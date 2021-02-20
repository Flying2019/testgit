#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
#define M 1000010
#define inf 100000000
using namespace std;
int nxt[M<<1],to[M<<1],head[N],f[N],cnt=1;
int add(int u,int v,int w)
{
    nxt[++cnt]=head[u];to[cnt]=v;f[cnt]=w;head[u]=cnt;
    nxt[++cnt]=head[v];to[cnt]=u;f[cnt]=0;head[v]=cnt;
    return cnt;
}
int dep[N],cur[N],all;
queue<int>q;
bool bfs(int s,int t)
{
    for(int i=1;i<=all;i++) dep[i]=inf,cur[i]=head[i];
    q.push(s);
    dep[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        if(f[i])
        {
            int v=to[i];
            if(dep[v]<dep[u]+1) continue;
            dep[v]=dep[u]+1;q.push(v);
        }
    }
    return dep[t]<inf;
}
int dfs(int u,int t,int fl)
{
    if(u==t || !fl) return fl;
    int res=0;
    for(int &i=head[u];i;i=nxt[i])
    {
        int v=to[i],fi=0;
        if(dep[v]==dep[u]+1 && (fi=dfs(v,t,min(fl,f[i]))))
        {
            f[i]-=fi;f[i^1]+=fi;
            fl-=fi;res+=fi;
        }
    }
    return res;
}
int dinic(int s,int t)
{
    int ans=0;
    while(bfs(s,t)) ans+=dfs(s,t,inf);
    return ans;
}
int ls[N],rs[N];
void build(int &u,int l,int r)
{
    if(l==r){u=l;return ;}
    u=++all;
    int mid=(l+r)>>1;
    build(ls[u],l,mid),build(rs[u],mid+1,r);
    add(u,ls[u],inf),add(u,rs[u],inf);
}
void insert(int u,int l,int r,int L,int R,int id)
{
    if(L<=l && r<=R){add(id,u,inf);return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(ls[u],l,mid,L,R,id);
    if(R>mid) insert(rs[u],mid+1,r,L,R,id);
}
int id[N],nid[N],n;
int fn[N],fm[N];
namespace tree{
    #define G 20010
    int nxt[G<<1],to[G<<1],head[G],cnt;
    void add(int u,int v)
    {
        nxt[++cnt]=head[u];
        to[cnt]=v;head[u]=cnt;
    }
    int dep[G],fa[G],son[G],siz[G],rt;
    void dfs1(int u,int p)
    {
        siz[u]=1;fa[u]=p;dep[u]=dep[p]+1;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(v==p) continue;
            dfs1(v,u);
            if(siz[son[u]]<siz[v]) son[u]=v;
        }
    }
    int top[G],idx;
    void dfs2(int u,int topp)
    {
        top[u]=topp;
        nid[id[u]=++idx]=u;
        if(son[u]) dfs2(son[u],topp);
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(v==fa[u] || v==son[u]) continue;
            dfs2(v,v);
        }
    }
    void init(int n)
    {
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v),add(v,u);
        }
        dfs1(1,0);
        dfs2(1,1);
        build(rt,1,n);
    }
    void adde(int u,int x,int y)
    {
        for(;top[x]!=top[y];x=fa[top[x]])
        {
            if(dep[top[x]]<dep[top[y]]) swap(top[x],top[y]);
            insert(rt,1,n,id[top[x]],id[x],u);
        }
        if(dep[x]>dep[y]) swap(x,y);
        insert(rt,1,n,id[x],id[y],u);
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    all=n+m;
    tree::init(n);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        tree::adde(i+n,x,y);
    }
    int s=++all;int t=++all;
    for(int i=1;i<=m;i++) fm[i]=add(s,i+n,1);
    for(int i=1;i<=n;i++) fn[i]=add(id[i],t,1);
    printf("%d\n",dinic(s,t));
    int t1=0,t2=0;
    for(int i=1;i<=n;i++)if(f[fn[i]]) t1++;printf("%d",t1);
    for(int i=1;i<=n;i++)if(f[fn[i]]) printf(" %d",i);puts("");
    for(int i=1;i<=m;i++)if(f[fm[i]]) t2++;printf("%d",t2);
    for(int i=1;i<=m;i++)if(f[fm[i]]) printf(" %d",i);puts("");
    return 0;
}