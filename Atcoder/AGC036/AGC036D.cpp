#include<iostream>
#include<cstdio>
#include<cstring>
#define N 510
#define ll long long
using namespace std;
ll f[N][N],a[N][N],b[N][N],sma[N][N],smb[N][N];
ll suma(int x1,int y1,int x2,int y2){return sma[x2][y2]-sma[x1-1][y2]-sma[x2][y1-1]+sma[x1-1][y1-1];}
ll sumb(int x1,int y1,int x2,int y2){return smb[x2][y2]-smb[x1-1][y2]-smb[x2][y1-1]+smb[x1-1][y1-1];}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(i<j) scanf("%d",&a[i][j]);
        else if(i>j) scanf("%d",&b[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) sma[i][j]=a[i][j]+sma[i-1][j]+sma[i][j-1]-sma[i-1][j-1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) smb[i][j]=b[i][j]+smb[i-1][j]+smb[i][j-1]-smb[i-1][j-1];
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) f[1][i]=suma(1,1,i,i);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int k=j+1;k<=n;k++)
                f[j+1][k]=min(f[j+1][k],f[i][j]+suma(j+1,j+1,k,k)+sumb(j+1,1,k,i-1));
    ll ans=1e17;
    for(int i=1;i<=n;i++) ans=min(ans,f[i][n]);
    printf("%lld\n",ans);
    return 0;
}