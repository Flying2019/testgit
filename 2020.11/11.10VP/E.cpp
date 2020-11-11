#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
#define mod 998244353
#define ll long long
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
int f[N][20],k;
int calc(int x,int v){for(int i=2;i<=k;i++) f[x][i]=(f[x][i]+f[x/v][i-1])%mod;}
int main()
{
    int n;
    scanf("%d%d",&n,&k);
    if(k>n){puts("0");return 0;}
    if(k==n){puts("1");return 0;}
    if(k==1){printf("%d\n",n);return 0;}
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    ll ans=C(n-1,k-1);//choose 1
    for(int i=2;i<=n;i++) ans=(ans+C(n/i-1,k-1))%mod;
    printf("%d\n",ans);
    return 0;
}