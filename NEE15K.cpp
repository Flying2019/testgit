#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define N 100010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    deg[u]++;
    head[u]=cnt;
}
int f[N],g[N],n;
bool vis[N];
void check()
{
    for(int i=1,u=f[1];i<n;i++,u=f[u])
    if(u==1) return;
    for(int i=1,u=1;i<=n;i++,u=f[u]) printf("%d ",u);
    puts("1");
    exit(0);
}
void dfs(int u)
{
    if(u>n){check();return;}
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(vis[v]) continue;
        f[u]=v;
        vis[v]=true;
        dfs(g[u]);
        vis[v]=false;
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    int u=0;
    for(int i=1;i<=n;i++)
    if(deg[i]>1) g[u]=i,u=i;
    else
    {
        if(deg[i]==0){puts("There is no route, Karl!");return 0;}
        int v=to[head[i]];f[i]=v;
        if(vis[v]){puts("There is no route, Karl!");return 0;}
        vis[v]=true;
    }
    g[u]=n+1;
    dfs(g[0]);
    puts("There is no route, Karl!");
    return 0;
}