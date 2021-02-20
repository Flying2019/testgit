#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int son[N],fa[N],d[N],head[N],nxt[N<<1],to[N<<1],cnt;
void add(int u,int v){nxt[++cnt]=head[u];to[cnt]=v;head[u]=cnt;}
void dfs(int u,int p)
{
    fa[u]=p;d[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];if(v==p) continue;
        dfs(v,u);if(d[u]<d[v]+1) d[u]=d[v]+1,son[u]=v;
    }
}
int arr[N<<3],*par=arr;
int* new_(int k,int p){par+=k+p+2;return par-p;}
int *f[N],*g[N];ll ans;
void solve(int u)
{
    if(son[u]) f[son[u]]=f[u]+1,g[son[u]]=g[u]-1,solve(son[u]);
    f[u][0]=1;ans+=g[u][0];
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];if(v==fa[u] || v==son[u]) continue;
        f[v]=new_(0,d[v]),g[v]=new_(d[v],d[v]);
        solve(v);
        for(int j=d[v];~j;j--) ans+=g[v][j]*f[u][j-1]+g[u][j+1]*f[v][j];
        for(int j=0;j<=d[v];j++) g[u][j]+=f[u][j]*f[v][j-1]+g[v][j+1],f[u][j]+=f[v][j-1];
    }
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
    dfs(1,0);f[1]=new_(0,d[1]),g[1]=new_(d[1],d[1]);
    solve(1);
    printf("%lld\n",ans);
    return 0;
}