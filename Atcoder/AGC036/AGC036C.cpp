#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3000010
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
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int calc(int x,int y){return C(x+y-1,y-1);}
int main()
{
    init();
    int n,m;
    scanf("%d%d",&n,&m);
    int ans=0;
    for(int i=m&1;i<=m;i+=2) ans=(ans+1ll*calc((3*m-i)/2,n)*C(n,i))%mod;
    printf("%lld\n",(ans-1ll*n*calc(m-1,n)%mod+mod)%mod);
    return 0;
}