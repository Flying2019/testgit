#include<iostream>
#include<cstdio>
#include<cstring>
#define N 600020
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
    return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;
}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
char s[N];
int Sn[N],n;
int calc(int x,int y){return C(x+y,x);}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    init();
    for(int i=Sn[0]=1;i<=n;i++) Sn[i]=(Sn[i-1]+C(n,i))%mod;
    int ans=ksm(2,n)-1;
    for(int l=1,r=1;l<=n;l=r+1)
    {
        for(r=l;r<=n && s[r]==s[l];r++);
        --r;
        for(int i=l;i<=r;i++) ans=(1ll*ans+calc(n-r-1,i)-C(n,i)+mod)%mod;
        for(int i=l;i<r;i++) ans=(ans+1ll*(i-l+1)*calc(n-i,l-2))%mod;
        for(int i=l+1;i<=r;i++) ans=(ans+1ll*(r-i+1)*calc(i-1,n-r-1))%mod;
        ans=(ans+1ll*(r-l+1)*calc(l-1,n-r))%mod;
    }
    printf("%d\n",ans);
    return 0;
}