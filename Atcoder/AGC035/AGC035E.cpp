#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
using namespace std;
int n,m,mod;
int f[N][N][N];
int main()
{
    scanf("%d%d%d",&n,&m,&mod);
    if(m%2==0)
    {
        static int f[N][N];
        memset(f,0,sizeof(f));
        f[0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=0;j<=m/2;j++) f[i][0]=(f[i][0]+f[i-1][j])%mod,f[i][j+1]=(f[i][j+1],f[i-1][j])%mod;
        int r1=0,r2=0;
        for(int i=0;i<=m/2;i++) r1=(r1+f[n/2][i])%mod,r2=(r2+f[(n+1)/2][i])%mod;
        printf("%d\n",1ll*r1*r2%mod);
        return 0;
    }
    f[0][0][0]=1;
    int p=(n+m)/2*2;
    for(int i=0;i<p;i+=2)
        for(int j=0;j<=n;j++)
            for(int k=0;k<=m+1;k++)
            {
                (f[i+2][0][0]+=f[i][j][k])%=mod;
                if(i<=n-2) (f[i+2][j+1][0]+=f[i][j][k])%=mod;
                if(i>=m-1) (f[i+2][0][k?k+1:0]+=f[i][j][k])%=mod;
                if(i<=n-2 && i>=m-1) (f[i+2][j+1][max(k+1,j+2)]+=f[i][j][k])%=mod;
            }
    int ans=0;
    for(int j=0;j<=n;j++)
        for(int k=0;k<=m+1;k++) ans=(ans+f[p][j][k])%mod;
    printf("%d\n",ans);
    return 0;
}