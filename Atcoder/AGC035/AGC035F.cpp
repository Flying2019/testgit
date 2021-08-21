#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
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
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    if(n>m) swap(n,m);
    int ans=0;
    for(int i=0;i<=n;i++) ans=(ans+(i&1?mod-1ll:1ll)*C(n,i)%mod*C(m,i)%mod*fac[i]%mod*ksm(n+1,m-i)%mod*ksm(m+1,n-i))%mod;
    printf("%d\n",ans);
    return 0;
}