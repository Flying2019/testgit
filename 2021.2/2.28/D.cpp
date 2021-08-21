#include<iostream>
#include<cstdio>
#include<cstring>
#define N 800010
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
int calc(int x,int y){return C(x+y,x);}//cut y into x
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int n,m;
int work(int x,int l,int r)
{
    if(x<1ll*r*m) return 0;
    int res=0;x-=r*m;
    for(int i=0;i<=n-m && x>=0;i++,x-=l)
    res=(res+(i&1?-1ll:1ll)*C(n-m,i)*calc(n,x)%mod+mod)%mod;
    return res;
}
int solve(int x)
{
    int res=0;
    for(int i=0;i<=x;i++)//The number at m
        res=(res+work(x,i,i)-work(x,i,i+1))%mod;
    return (calc(n,x)-1ll*res*C(n,m)%mod+mod)%mod;
}
int main()
{
    int l,r;
    scanf("%d%d%d%d",&n,&m,&l,&r);
    init();
    printf("%d\n",(solve(r)-solve(l-1)+mod)%mod);
    return 0;
}