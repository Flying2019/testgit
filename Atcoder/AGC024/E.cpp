#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
using namespace std;
int f[N][N][N],mod;
int main()
{
    int n,m;
    scanf("%d%d%d",&n,&m,&mod);
    for(int i=1;i<=m;i++) f[1][i][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            for(int k=i;k;k--) f[i+1][j][k]=(f[i+1][j][k]+1ll*f[i][j][k]*(k+1))%mod,f[i][j][k-1]=(f[i][j][k-1]+f[i][j][k])%mod;
            f[i][j+1][i]=(f[i][j+1][i]+f[i][j][0])%mod;
            f[i+1][j][0]=(f[i+1][j][0]+f[i][j][0])%mod;
        }
    printf("%d\n",f[n][m][0]);
    return 0;
}