#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 300010
#define ll long long
#define lll __int128
using namespace std;
int nxt[N<<1],to[N<<1],id[N<<1],head[N],cnt;
void add(int u,int v,int w)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;id[cnt]=w;
    head[u]=cnt;
}
struct node{
    int x,y;ll w;
    bool operator <(const node a)const{return w>a.w;}
}r[M];
int f[N];bool use[M];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int dep[N],fa[N],son[N],siz[N],top[N];
void dfs(int u,int p)
{
    fa[u]=p,siz[u]=1;
    dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int topp)
{
    top[u]=topp;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa[u] || v==son[u]) continue;
        dfs2(v,v);
    }
}
int lca(int x,int y)
{
    for(;top[x]!=top[y];x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
    return dep[x]<dep[y]?x:y;
}
ll g[N];
void work(int u,int q)
{
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa[u]) continue;
        work(v,id[i]);g[u]+=g[v];
    }
    if(q) r[q].w+=g[u];
}
int h[N][32][2],n,m;
void print(lll x)
{
    if(x>=10) print(x/10);
    putchar('0'+(int)(x%10));
}
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++) scanf("%d%d%lld",&r[i].x,&r[i].y,&r[i].w);
    sort(r+1,r+m+1);
    for(int i=1;i<=m;i++)
    if(find(r[i].x)!=find(r[i].y))
    {
        use[i]=true;add(r[i].x,r[i].y,i),add(r[i].y,r[i].x,i);
        f[find(r[i].x)]=r[i].y;
    }
    dfs(1,0);dfs2(1,1);
    for(int i=1;i<=m;i++)
    if(!use[i]) g[r[i].x]+=r[i].w,g[r[i].y]+=r[i].w,g[lca(r[i].x,r[i].y)]-=2*r[i].w;
    work(1,0);
    int m1=0;
    for(int i=1;i<=m;i++)
    if(use[i]) r[++m1]=r[i];
    sort(r+1,r+m1+1);
    for(int i=1;i<=n;i++)
    {
        f[i]=i;
        for(int k=31;~k;k--) h[i][k][i>>k&1]++;
    }
    lll ans=0;
    for(int i=1;i<=m1;i++)
    {
        int x=find(r[i].x),y=find(r[i].y);
        for(int k=31;~k;k--)
        if(r[i].w>>k&1) ans+=(lll)(1ll<<k)*(1ll*h[x][k][0]*h[y][k][0]+1ll*h[x][k][1]*h[y][k][1]);
        else ans+=(lll)(1ll<<k)*(1ll*h[x][k][0]*h[y][k][1]+1ll*h[x][k][1]*h[y][k][0]);
        f[x]=y;
        for(int k=31;~k;k--)
            for(int _=0;_<=1;_++) h[y][k][_]+=h[x][k][_];
    }
    print(ans);puts("");
}
void clear()
{
    for(int i=1;i<=n;i++) memset(h[i],0,sizeof(h[i])),head[i]=g[i]=son[i]=0;
    for(int i=1;i<=m;i++) use[i]=false;
    cnt=0;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0) solve(),clear();
    return 0;
}