#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 998244353
#define ll long long
using namespace std;
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
int fac[N],inv[N];
void init(int n=N-10)
{
    for(int i=fac[0]=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    int res=0;
    for(int i=1;i<=min(n,m);i++) res=(res+1ll*C(2*i,i)*C(n+m-2*i,n-i))%mod;
    res=1ll*res*ksm(C(n+m,m))%mod*ksm(2)%mod;
    printf("%d\n",(res+max(n,m))%mod);
    return 0;
}
