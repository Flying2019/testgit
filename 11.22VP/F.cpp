#include<iostream>
#include<cstdio>
#include<cstring>
#define N 4010
#define mod 998244353
using namespace std;
int fac[10010],inv[10010];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int P(int a,int b){return a<b?0:1ll*fac[a]*inv[a-b]%mod;}
bool ax[N],ay[N];
int f[N][N/2],g[N][N/2];
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    fac[0]=1;
    for(int i=1;i<=n+m;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n+m]=ksm(fac[n+m]);
    for(int i=n+m-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=k;i++)
    {
        int cx,cy,dx,dy;
        scanf("%d%d%d%d",&cx,&cy,&dx,&dy);
        ax[cx]=ax[dx]=ay[cy]=ay[dy]=true;
    }
    ax[0]=ay[0]=true;
    int sx=0,sy=0;
    for(int i=1;i<=n;i++) sx+=!ax[i];
    for(int i=1;i<=m;i++) sy+=!ay[i];
    f[0][0]=g[0][0]=true;
    for(int i=1;i<=n;i++)
    {
        f[i][0]=1;
        for(int j=1;2*j<=i;j++)
        f[i][j]=(f[i-1][j]+(ax[i] || ax[i-1]?0:f[i-2][j-1]))%mod;
    }
    for(int i=1;i<=m;i++)
    {
        g[i][0]=1;
        for(int j=1;2*j<=i;j++)
        g[i][j]=(g[i-1][j]+(ay[i] || ay[i-1]?0:g[i-2][j-1]))%mod;
    }
    int ans=0;
    for(int i=0;2*i<=sx;i++)
        for(int j=0;2*j<=sy;j++)
        ans=(ans+1ll*f[n][i]*g[m][j]%mod*P(sx-2*i,j)%mod*P(sy-2*j,i))%mod;
    printf("%d",ans);
    return 0;
}