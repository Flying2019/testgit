#include<iostream>
#include<cstdio>
#include<cstring>
#define N 610
#define mod 1000000007
using namespace std;
int f[N][N],g[N],r[N][N];
int mn[N][N],mx[N][N];
int a[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        a[u]=v,a[v]=u;
    }
    n*=2;
    g[0]=1;
    for(int i=2;i<=n;i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) r[i][j]=r[i][j-1]+(!a[j]);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) mn[i][j]=a[j] && mn[i][j-1]?min(mn[i][j-1],a[j]):mn[i][j-1]+a[j];
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) mx[i][j]=a[j] && mx[i][j-1]?max(mx[i][j-1],a[j]):mx[i][j-1]+a[j];
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        if((!mn[i][j] || mn[i][j]>=i) && (!mx[i][j] || mx[i][j]<=j))
        {
            f[i][j]=g[r[i][j]];
            for(int k=i+1;k<j;k++) f[i][j]=(f[i][j]-1ll*f[i][k]*g[r[k+1][j]]%mod+mod)%mod;
        }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) ans=(ans+1ll*f[i][j]*g[n-m*2-r[i][j]])%mod;
    printf("%d\n",ans);
    return 0;
}