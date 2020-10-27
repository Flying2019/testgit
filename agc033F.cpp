#include<iostream>
#include<cstdio>
#include<cstring>
#define N 210
using namespace std;
char s[N][N];
int f[2][N][N][N];
int main()
{
    int n,m,u=1;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++) scanf("%s",s[i]+1);
    for(int j=1;j<=m;j++)
        for(int i=j;i;i--)
            for(int k=n;k;k--)
            if(i==j) f[u][i][j][k]=s[i][k]==s[i][k+1]?f[u][i][j][k+1]:k+1;
            else f[u][i][j][k]=s[j-1][k]==s[j][k]?min(f[u][i][j-1][k],f[u][j][j][k]):k;
    for(int ans=0;ans<=n;ans++)
    {
        if(f[u][1][m][1]==n+1){printf("%d\n",ans);return 0;}
        int p=u;u=!u;
        for(int lf=1;lf<=m;lf++)
            for(int rf=lf;rf<=m;rf++)
                for(int k=1;k<=n;k++)
                {
                    if(f[p][lf][rf][k]==n+1) f[u][lf][rf][k]=n+1;
                    else f[u][lf][rf][k]=f[p][lf][rf][f[p][lf][rf][k]];
                    for(int l=lf,r=rf;l<=r;)
                    {
                        int mid=(l+r)>>1;
                        f[u][lf][rf][k]=max(f[u][lf][rf][k],min(f[p][lf][mid][k],f[p][mid+1][rf][k]));
                        if(f[p][lf][mid][k]>f[p][mid+1][rf][k]) l=mid+1;
                        else r=mid-1;
                    }
                }
    }
    return 0;
}