#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
#define mod 1000000007
using namespace std;
int c[N],a[N];
int fac[N],inv[N];
int ksm(int a,int b=mod-2)
{
    if(b<0) b+=mod-1;
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
int f[N][N],g[N][N],h[N][N],s[N];
//f[i][j]:i个点连j条边乘上容斥系数的答案
//g[i][j]:第i种颜色点，已连j条边的答案
//h[i][j]:i个点分成j块，每块<=k的方案数
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++) scanf("%d",&c[i]),a[c[i]]++;
    h[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            for(int p=1;p<=min(i,k);p++)
                h[i][j]=(h[i][j]+1ll*ksm(p,p-2)*p%mod*C(i-1,p-1)%mod*h[i-p][j-1]%mod)%mod;
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)s[i]=(s[i]+(j&1?1ll:-1ll)*h[i][j]*ksm(i,j-1)%mod+mod)%mod;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            for(int p=1;p<=i;p++)
                f[i][j]=(f[i][j]+1ll*s[p]*f[i-p][j-1]%mod*C(i-1,p-1)%mod+mod)%mod;
    g[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
            for(int p=0;p<=min(a[i],j);p++)//分成p组
                g[i][j]=(g[i][j]+1ll*g[i-1][j-p]*f[a[i]][p])%mod;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=(ans+1ll*g[n][i]*ksm(n,i-2)%mod)%mod;
    printf("%d\n",ans);
    return 0;
}