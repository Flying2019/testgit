#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 300010
#pragma GCC optimize(2)
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
vector<int>g[N],h[N];
int fa[N],siz[N],dep[N],son[N];
void dfs(int u,int p)
{
    fa[u]=p;siz[u]=1;dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        if(siz[v]>siz[son[u]]) son[u]=v;
        siz[u]+=siz[v];
    }
}
int top[N];
void dfs2(int u,int topp)
{
    top[u]=topp;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==son[u] || v==fa[u]) continue;
        dfs2(v,v);
    }
}
int lca(int x,int y)
{
    for(;top[x]!=top[y];x=fa[top[x]])
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    return dep[x]<dep[y]?x:y;
}
int ar[N*4];int *fu=ar,*fd=ar+N*2;
int w[N],d[N],val[N],ans[N];
int x[N],y[N];
void solve(int u)
{
    int lu=w[u]+dep[u],ld=w[u]-dep[u],tu=fu[lu],td=fd[ld];
    for(int i=head[u];i;i=nxt[i])
    if(to[i]!=fa[u]) solve(to[i]);
    fu[dep[u]]+=val[u];
    for(int v:g[u]) fd[d[v]-dep[y[v]]]++;
    ans[u]+=fu[lu]-tu+fd[ld]-td;
    for(int v:h[u]) fu[dep[x[v]]]--,fd[d[v]-dep[y[v]]]--;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        int l=lca(x[i],y[i]);
        d[i]=dep[x[i]]+dep[y[i]]-2*dep[l];
        val[x[i]]++;
        g[y[i]].push_back(i),h[l].push_back(i);
        if(dep[l]+w[l]==dep[x[i]]) ans[l]--;
    }
    solve(1);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}