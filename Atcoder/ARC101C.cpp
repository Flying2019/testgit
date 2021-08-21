#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define mod 1000000007
using namespace std;
int f[N][N];
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int siz[N],g[N],h[N];
void dfs(int u,int p)
{
    siz[u]=1;f[u][1]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        for(int i=1;i<=siz[u];i++)
            for(int j=0;j<=siz[v];j++)
            g[i+j]=(g[i+j]+1ll*f[u][i]*f[v][j])%mod;
        siz[u]+=siz[v];
        for(int i=1;i<=siz[u];i++) f[u][i]=g[i],g[i]=0;
    }
    for(int i=2;i<=siz[u];i+=2) f[u][0]=(f[u][0]-1ll*f[u][i]*h[i]%mod+mod)%mod;
}
int main()
{
    int n;
    scanf("%d",&n);
    h[0]=1;
    for(int i=2;i<=n;i++) h[i]=1ll*(i-1)*h[i-2]%mod;
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    printf("%d\n",mod-f[1][0]);
    return 0;
}