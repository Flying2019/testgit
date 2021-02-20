#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 1000000007
using namespace std;
int f[N][2],g[2],h[2];
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;deg[u]++;
    head[u]=cnt;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=2,a;i<=n;i++)
    {
        scanf("%d",&a);
        add(a,i);
    }
    for(int u=n;u>=1;u--)
    {
        f[u][1]=1;
        if(!deg[u]) continue;
        h[0]=1;h[1]=0;
        int a=1;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i],t=f[u][0];
            f[u][0]=(f[u][0]+1ll*t*f[v][0]+1ll*f[u][1]*f[v][1])%mod;
            f[u][1]=(f[u][1]+1ll*t*f[v][1]+1ll*f[u][1]*f[v][0])%mod;
            t=h[0], h[0]=1ll*h[1]*f[v][1]%mod;
            h[1]=1ll*t*f[v][1]%mod;
            a=1ll*a*f[v][0]%mod;
        }
        f[u][0]=(f[u][0]*2ll-h[1]+mod)%mod;
        f[u][1]=(f[u][1]*2ll-a+mod)%mod;
    }
    printf("%d\n",(f[1][1]+f[1][0])%mod);
    return 0;
}