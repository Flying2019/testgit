#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1510
using namespace std;
int f[N][N],s[N][N];
int l[N][N],r[N][N],n;
char str[N];
void erase(int x,int y)
{
    if(!f[x][y] || f[x-1][y] || f[x][y-1]) return;
    for(int i=y;i<=n;i++) s[x][i]-=f[x][y];
    f[x][y]=0;
    erase(x+1,y),erase(x,y+1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        for(int j=1;j<=n;j++)
            f[i][j]=str[j]!='#'?str[j]-'0':0,s[i][j]=s[i][j-1]+f[i][j];
    }
    memset(l,0x3f,sizeof(l));
    long long ans=0;
    for(int i=n;i;i--)
        for(int j=n;j;j--)
        if(f[i][j])
        {
            int t=0;
            l[j][i]=r[j][i]=j;
            for(int k=i;k<=n;k++)
            {
                l[j][k]=min(l[j][k],l[j+1][k]);
                r[j][k]=max(r[j][k],r[j+1][k]);
                if(l[j][k]<=r[j][k]) t+=s[k][r[j][k]]-s[k][l[j][k]-1];
            }
            ans+=f[i][j]*(t-f[i][j]);
            erase(i,j);
        }
        else memset(l[j]+i,0x3f,sizeof(int)*(n-i+1)),memset(r[j]+i,0,sizeof(int)*(n-i+1));
    printf("%lld\n",ans);
    return 0;
}