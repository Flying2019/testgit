#include<iostream>
#include<cstdio>
#include<cstring>
#define N 20000010
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
int C(int a,int b)
{
    if(a==b) return 1;
    return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;
}
int calc(int a,int b){return C(a+b-1,b-1);}
int qry(int a,int b){return (calc(a,b)-calc(a-1,b+1)+mod)%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int main()
{
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    init();
    int ans=0;
    for(int i=0;i<=a;i++)
    {
        if(n-b<i) break;
        if(n-b==i){if(i==a) ans=(ans+qry(i,b))%mod;continue;}
        ans=(ans+1ll*qry(i,b)*calc(n-b-i-1,a-i+1))%mod;
    }
    printf("%d\n",ans);
    return 0;
}