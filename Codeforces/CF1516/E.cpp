#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define N 210
using namespace std;
int f[N*2][N*2][N];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int iv[N*2];
int C(int n,int k)
{
    int r=1;
    for(int i=1;i<=k;i++) r=1ll*r*(n-i+1)%mod*iv[i]%mod;
    return r;
}
int ans[N*2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=2*m;i++) iv[i]=ksm(i);
    f[0][0][0]=1;
    for(int i=0;i<=2*m;i++)
        for(int j=0;j<=i;j++)//lian
            for(int k=0;j+2*k<=i;k++)//huan
            if(f[i][j][k])
            {
                f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k])%mod;
                f[i+1][j][k]=(f[i+1][j][k]+1ll*f[i][j][k]*j*2%mod)%mod;//合到链上
                if(j) f[i+1][j-1][k+1]=(f[i+1][j-1][k+1]+1ll*f[i][j][k]*j)%mod;//合链成环
                if(j) f[i+1][j-1][k]=(f[i+1][j-1][k]+2ll*f[i][j][k]*(1ll*j*(j-1)/2%mod)%mod)%mod;//合并两条链
            }
    for(int i=0;i<=min(n,2*m);i++)
        for(int j=0;2*j<=i;j++)
        if(f[i][0][j])
        {
            int x=i-j;
            ans[x]=(ans[x]+1ll*f[i][0][j]*C(n,i))%mod;
        }
    for(int i=2;i<=m;i++) ans[i]=(ans[i]+ans[i-2])%mod;
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
    return 0;
}