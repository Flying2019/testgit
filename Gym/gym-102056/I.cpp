#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define ll long long
using namespace std;
const ll Minn=(ll)0xcfcfcfcfcfcfcfcf;
ll f[N][N*N],g[N][N*N];
int a[N],b[N],c[N];
int main()
{
    int T;
    scanf("%d",&T);
    memset(f,0xcf,sizeof(f));
    while(T --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&c[i]);
        f[0][0]=0;
        for(int i=n;i>=1;i--)
        {
            for(int j=0;j<=n-i;j++)
                for(int k=0;k<=(n-i)*j;k++) g[j][k]=f[j][k],f[j][k]=Minn;
            for(int j=0;j<=n-i;j++)
                for(int k=0;k<=(n-i)*j;k++)
                {
                    f[j+1][j+k+1]=max(f[j+1][j+k+1],g[j][k]+a[i]);//choose A
                    f[j][j+k]=max(f[j][j+k],g[j][k]+1ll*b[i]*k);//choose B
                    f[j][j+k]=max(f[j][j+k],g[j][k]+1ll*c[i]*j);//choose C
                }
        }
        ll ans=0;
        for(int j=0;j<=n;j++)
            for(int k=0;k<=n*j;k++) ans=max(ans,f[j][k]),f[j][k]=Minn;
        printf("%lld\n",ans);
    }
    return 0;
}