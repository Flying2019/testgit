#include<iostream>
#include<cstdio>
#include<cstring>
#define N 410
#define mod 998244353
using namespace std;
int fac[N],inv[N];
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
int f[N][N][N];
int a[N],b[N];
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int main()
{
    init();
    int n,sa=0,sb=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]),sa+=a[i],sb+=b[i];
    f[0][0][0]=mod-sa;
    for(int i=1;i<=n;i++)
    {
        memcpy(f[i],f[i-1],sizeof(f[i]));
        for(int j=a[i];j<=sa;j++)
            for(int k=0;k<=sb;k++)
                for(int l=0,ca=1;l<=min(b[i]-1,k);l++,ca=1ll*ca*a[i]%mod)
                f[i][j][k]=(f[i][j][k]-1ll*f[i-1][j-a[i]][k-l]*ca%mod*inv[l]%mod+mod)%mod;
    }
    int ans=0;
    for(int i=1;i<=sa;i++)
    {
        int iv=ksm(i),ca=iv;
        for(int j=0;j<=sb;j++,ca=1ll*ca*iv%mod) ans=(ans+1ll*f[n][i][j]*fac[j]%mod*ca)%mod;
    }
    printf("%d\n",ans);
    return 0;
}