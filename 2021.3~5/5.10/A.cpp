#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int mod=998244353,N=510;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int fac[N],inv[N],iv[N];
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    iv[1]=1;
    for(int i=2;i<=n;i++) iv[i]=1ll*(mod-mod/i)*iv[mod%i]%mod;
}
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
vector<int>g[N];
const int M=155;
int siz[M],n;
int f[M][M][M],h[M][M];
inline void add(int &u,int v){if(u+v>=mod) u+=v-mod;else u+=v;}
void dfs(int u,int p)
{
    f[u][0][0]=1;
    for(int v:g[u])
    if(v!=p)
    {
        dfs(v,u);
        for(int i=0;i<=siz[u];i++)
            for(int j=i;j<=siz[u];j++) h[i][j]=f[u][i][j],f[u][i][j]=0;
        for(int i=0;i<=siz[u];i++)
            for(int j=i;j<=siz[u];j++)
                for(int i0=0;i0<=siz[v];i0++)
                    for(int j0=i0;j0<=siz[v];j0++)
                        add(f[u][i+i0][j+j0],1ll*h[i][j]*f[v][i0][j0]%mod*C(j+j0,j)%mod*C(siz[u]+siz[v]-j0-j,siz[u]-j)%mod);
        siz[u]+=siz[v];
    }
    for(int i=0;i<=siz[u];i++)
        for(int j=i;j<=siz[u];j++) h[i][j]=f[u][i][j],f[u][i][j]=0;
//  printf("%d:\n",u);
//  for(int i=0;i<=siz[u];i++,puts(""))
//      for(int j=0;j<=siz[u];j++) printf("%d ",f[u][i][j]);
    siz[u]++;
    for(int i=0;i<=siz[u];i++)
        for(int j=i;j<=siz[u];j++) add(f[u][i][j],1ll*h[i][j]*(siz[u]-j)%mod);
    for(int i=0;i<siz[u];i++)
        for(int j=i;j<=siz[u];j++)
            for(int k=0;k<j;k++) add(f[u][i+1][j],h[i][k]);
//  for(int i=0;i<=siz[u];i++,puts(""))
//      for(int j=0;j<=siz[u];j++) printf("%d ",f[u][i][j]);
//  int ans=0;
//  for(int i=0;i<=siz[u];i++) add(ans,f[u][i][siz[u]]);
//  printf("%d\n",ans);
//  puts("");
}
int main()
{
    init();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);g[v].push_back(u);
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=m;i++) add(ans,f[1][i][n]);
    printf("%d\n",1ll*ans*inv[n]%mod);
    return 0;
}