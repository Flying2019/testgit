#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
using namespace std;
int f[N][N],mod,g[N][N];
int main()
{
    int n;
    scanf("%d%d",&n,&mod);
    f[0][0]=g[0][0]=1;
    for(int i=1;i<=(n+1)/2;i++)
        for(int j=0;j<=n;j++)
            for(int k=j;k<=n;k+=i) f[i][k]=(f[i][k]+f[i-1][j])%mod;
    for(int i=(n-1)/2;i;i--)
        for(int j=0;j<=n && i*j<n;j++)
            for(int k=i*j;k<=n-i;k++) g[j+1][k+i]=(g[j+1][k+i]+g[j][k])%mod;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
        g[i][j]=(1ll*g[i][j]+(i?g[i-1][j]:0)+(j?g[i][j-1]:0)-(i && j?g[i-1][j-1]:0)+mod)%mod;
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<i;j++) ans=(ans+1ll*f[n/2][j]*g[n-i][i-j-1])%mod;
    printf("%d\n",ans);
    return 0;
}