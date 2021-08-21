#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define mod 1000000007
using namespace std;
int f[N][N],g[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) f[0][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1,s=0;j<=m;j++) g[j]=(2ll*g[j-1]+1ll*f[i-1][j]*j)%mod;
        for(int j=1,s=0;j<=m;j++) f[i][j]=(1ll*f[i-1][j]*(j+1)%mod+g[j-1])%mod;
    }
    printf("%d\n",f[n][m]);
    return 0;
}