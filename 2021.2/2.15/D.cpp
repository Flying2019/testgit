#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 1000000007
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
int C(int a,int b){return a<0 || b<0 || a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int f[N];
int main()
{
    int n;
    scanf("%d",&n);
    init();
    for(int i=1;i<=n;i++)
    {
        int tot=0,res=0;
        for(int k=2;k<=n;k++)
        {
            int r=n+i-1-k*i;
            if(r<0) break;
            tot=(tot+C(k+r,k))%mod;
        }
        for(int k=2;k<=n;k++)
        {
            int r=n-1-(k-1)*(i-1);
            if(r+1<k) break;
            res=(res+1ll*(n+1)*C(r+1,k)%mod-C(r+2,k+1)+mod)%mod;
        }
        f[i]=(2ll*res-1ll*(n+1)*tot%mod+mod)%mod;
    }
    int ans=0;
    for(int i=n;i>=1;i--) ans=(ans+1ll*(f[i-1]-f[i]+mod)*i)%mod;
    printf("%d\n",ans);
    return 0;
}