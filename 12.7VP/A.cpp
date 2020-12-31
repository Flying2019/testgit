#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
using namespace std;
int f[N][N];
char s[N][N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    f[1][1]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        f[i+1][j]=min(f[i+1][j],f[i][j]+(s[i][j]!=s[i+1][j])),f[i][j+1]=min(f[i][j+1],f[i][j]+(s[i][j]!=s[i][j+1]));
    printf("%d\n",(f[n][m]+(s[1][1]=='#')+(s[n][m]=='#'))/2);
    return 0;
}