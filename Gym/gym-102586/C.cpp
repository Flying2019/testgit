#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
#define mod 998244353
#define ll long long
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int a[N],n;
ll m,k;
int f[N],g[N],h[N];
void get_mod()
{
    for(int i=n-1;i>=0;i--)
    if(f[i+n])
    {
        int v=f[i+n];
        for(int j=n;j;j--) f[i+j]=(f[i+j]-1ll*v*g[j]+mod)%mod;
    }
}
int res[N];
void get_mul(int f[],int g[])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        h[i+j]=(f[i+j]+1ll*f[i]*g[j])%mod;
    for(int i=0;i<n*2;i++) f[i]=h[i],h[i]=0;
}
void get_pow(ll k)
{
    res[0]=1;f[1]=1;
    for(;k;k>>=1,get_mul(f,f),get_mod()) if(k&1) get_mul(res,f);
}
void get_nxt()
{
    for(int i=n;i;i--) res[i]=res[i-1];res[0]=0;
    get_mod();
}
namespace gauss{
    int a[N][N];
    void work(int n)
    {
        for(int i=1;i<=n;i++);
    }
}
int main()
{
    int s=0;
    scanf("%d%lld%lld",&n,&m,&k);
    for(int i=0;i<n;i++) scanf("%d",&a[i]),s+=a[i];
    s=ksm(s);
    for(int i=0;i<n;i++) a[i]=1ll*a[i]*s%mod,g[i]=mod-a[i];
    g[n]=1;
    ll X=m-k-1;
    get_pow(X);
    for(int i=1;i<=n;i++) gauss::a[1][i]=res[i-1];
    get_pow(m-1);
    for(int i=1;i<n;i++)
        for(int j=0;j<n;j++) gauss::a[i+1][j]=res[j+1]-(i==j+1);
    return 0;
}