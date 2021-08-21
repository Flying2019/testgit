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
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int _3[N];
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    init();
    int s=n+m+k,ans=0,r=1;
    if(m<k) swap(m,k);
    for(int i=_3[0]=1;i<=s;i++) _3[i]=_3[i-1]*3ll%mod;
    for(int i=0;i<=m+k;i++)
    {
        ans=(ans+1ll*r*C(n+i-1,n-1)%mod*_3[m+k-i]%mod)%mod;
        r=(r*2ll-C(i,k)-C(i,i-m)+2ll*mod)%mod;
    }
    printf("%d\n",ans);
    return 0;
}