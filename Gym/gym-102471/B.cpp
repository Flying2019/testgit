#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
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
int calc(int n,int m,int k)
{
    if(n>m) swap(n,m);k+=n/2;
    return 1ll*C((n+m)/2,k)*C((n+m)/2,n-k)%mod;
}
int main()
{
    int t;
    scanf("%d",&t);
    init();
    while(t --> 0)
    {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        if((n+m)%2==0) printf("%d\n",calc(n,m,k));
        else printf("%d\n",(calc(n,m-1,k)+calc(n-1,m,k+(n&1?-1:1)*(m&1)))%mod);
    }
    return 0;
}