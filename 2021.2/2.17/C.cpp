#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
#define C 26
using namespace std;
char s[N],t[N];
int c1[N][C],c2[N][C],f[N][N];
int main()
{
    scanf("%s%s",s+1,t+1);
    int n=strlen(s+1);
    for(int i=n;i>=1;i--) memcpy(c1[i],c1[i+1],sizeof(c1[i])),c1[i][s[i]-'a']++;
    for(int i=n;i>=1;i--) memcpy(c2[i],c2[i+1],sizeof(c2[i])),c2[i][t[i]-'a']++;
    for(int i=0;i<C;i++) if(c1[1][i]!=c2[1][i]){puts("-1");return 0;}
    for(int i=0;i<=n;i++) f[0][i]=f[i][0]=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            f[i][j]=min(f[i-1][j],f[i][j-1]);
            if(s[i]!=t[j]) continue;
            bool b=true;
            for(int k=0;k<C;k++) if(c1[i][k]<c2[j][k]) b=false;
            if(b) f[i][j]=min(f[i][j],f[i-1][j-1]-1);
        }
    printf("%d\n",f[n][n]);
    return 0;
}