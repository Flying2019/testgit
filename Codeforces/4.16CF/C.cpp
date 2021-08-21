#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#define N 200010
#define M 1010
#define ll long long
using namespace std;
int x[N],y[N],w[N];
bool cut[N];
bool mp[M][M];
int f[N],id[N],qd[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int nxt[M<<1],to[M<<1],wid[M<<1],head[M],cnt;
void add(int u,int v,int w)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;wid[cnt]=w;
    head[u]=cnt;
}
bool rm[M];
int wq[M],fa[M],dep[M];
void dfs(int u,int p)
{
    dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);fa[v]=u;wq[v]=wid[i];
    }
}
int all=0;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&x[i],&y[i],&w[i]),all^=w[i];
    for(int i=1;i<=m;i++) id[i]=i;
    if((n-1)*(n-2)/2>=m){c1::solve(n,m);return 0;}
    for(int i=1;i<=m;i++) mp[x[i]][y[i]]=mp[y[i]][x[i]]=true;
    for(int i=1;i<=n;i++) f[i]=i;
    bool can=true;
    for(int i=1;i<=n && can;i++)
        for(int j=i+1;j<=n && can;j++)
        if(!mp[i][j]){if(find(i)==find(j)) can=false;else f[find(i)]=find(j);}
    if(!can){c1::solve(n,m);return 0;}
    sort(id+1,id+m+1,[&](int x,int y){return w[x]<w[y];});
    for(int i=1;i<=n && can;i++)
        for(int j=i+1;j<=n && can;j++)
        if(!mp[i][j]) add(i,j,0),add(j,i,0);
    ll ans=0;
    for(int i=1;i<=m;i++)
    {
        int u=id[i];
        if(find(x[u])!=find(y[u])) f[find(x[u])]=find(y[u]),add(x[u],y[u],1),add(y[u],x[u],1),ans+=w[u];
        else rm[i]=true;
    }
    for(int i=1;i<=m;i++)
    if(rm[i])
    {
        int u=id[i];
        if(w[u]>all){printf("%lld\n",ans+all);return 0;}
        int p=x[i],q=y[i];
        bool hv=false;
        for(;p!=q;p=fa[p])
        {
            if(dep[p]<dep[q]) swap(p,q);
            if(wq[p]==0){hv=true;break;}
        }
        if(hv){printf("%lld\n",ans+w[u]);return 0;}
    }
    printf("%lld\n",ans+all);
    return 0;
}