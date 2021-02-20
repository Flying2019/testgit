#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2000010
#define mod 998244353
#define G 3
#define Gi ((mod+1)/G)
using namespace std;
int f[N],g[N],inv[N];
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
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    if(k==1){puts("1");return 0;}
    n/=2;
    int mx=0;
    for(int i=1;i<=k;i++)
    {
        int x;
        scanf("%d",&x);
        f[x]=1,mx=max(mx,x);
    }
    inv[1]=1;
    for(int i=2;i<=N-10;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    int mn=0;
    for(int i=0;i<=mx && !f[i];i++) mn=max(mn,i+1);
    if(mn) for(int i=0;i<=mx;i++) f[i]=f[i+mn];
    mx-=mn;
    for(int i=0;i<n*mx;i++)
    {
        int r=0;
        for(int j=0;j<=min(i,mx-1);j++) r=(r+1ll*(j+1)*f[j+1]%mod*g[i-j])%mod;
        for(int j=0;j<=min(i,mx-1);j++) r=(r-1ll*(j+1)*g[j+1]%mod*g[i-j])%mod;
    }
    return 0;
}