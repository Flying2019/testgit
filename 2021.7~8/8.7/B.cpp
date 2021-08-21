#include<iostream>
#include<cstdio>
#include<cstring>
#define N 20
using namespace std;
int vis[N][N];
bool f[N][N];
char s[N][N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        memset(f,0,sizeof(f));memset(vis,0,sizeof(vis));
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
        f[n][n]=true;
        for(int i=n;i;i--)
            for(int j=n;j;j--)
            if(s[i][j]=='#') f[i][j]=false;
            else if(f[i][j]) f[i-1][j]=f[i][j-1]=true;
        if(!f[1][1]){puts("0");continue;}
        int x=1,y=1;
        while(x!=n || y!=n)
        {
            if(x!=n && f[x+1][y]) x++;
            else y++;
            vis[x][y]++;
        }
        x=1;y=1;
        while(x!=n || y!=n)
        {
            if(y!=n && f[x][y+1]) y++;
            else x++;
            vis[x][y]++;
        }
        // for(int i=1;i<=n;i++,puts(""))
        //     for(int j=1;j<=n;j++) printf("%d ",vis[i][j]);
        bool can=true;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            if(!(i==1 && j==1) && !(i==n && j==n) && vis[i][j]==2) can=false;
        printf("%d\n",1+can);
    }
    return 0;
}