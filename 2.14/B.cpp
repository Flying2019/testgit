#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
using namespace std;
char s[N][N];
int n,m;
int f[N][N];
int dfs(int x, int y)
{
    if(~f[x][y]) return f[x][y];
    if(x>n || y>m) return 0;
    int &u=f[x][y];u=0;
    if(x<n && y<m && s[x+1][y]==s[x][y+1]) u=true;
    u|=dfs(x+1,y)|dfs(x,y+1);
    return u;
}
int main()
{
    memset(f,-1,sizeof(f));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    dfs(1,1);
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
        if(s[i+1][j]==s[i][j+1])
        {
            if(f[i+1][j+1]){puts("YES");return 0;}
            if(i<n-1 && s[i+1][j+1]==s[i+2][j]){puts("YES");return 0;}
            if(j<m-1 && s[i+1][j+1]==s[i][j+2]){puts("YES");return 0;}
        }
    puts("NO");
    return 0;
}