#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int dep[N];
void dfs(int u,int p)
{
    dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
    }
}
int id[N],tt;
int son[N],fa[N];
void dfs2(int u,int p)
{
    fa[u]=p;dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs2(v,u);
    }
}
void dfs3(int u)
{
    id[u]=++tt;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==son[u] || v==fa[u]) continue;
        dfs3(v);
        ++tt;
    }
    if(son[u]) dfs3(son[u]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    int a=0;
    for(int i=1;i<=n;i++) if(!a || dep[a]<dep[i]) a=i;
    dfs2(a,0);
    int b=0;
    for(int i=1;i<=n;i++) if(!b || dep[b]<dep[i]) b=i;
    for(int i=b;i!=a;i=fa[i]) son[fa[i]]=i;
    dfs3(a);
    for(int i=1;i<=n;i++) printf("%d ",id[i]);
    return 0;
}