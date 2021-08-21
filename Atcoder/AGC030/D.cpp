#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
#define mod 1000000007
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
const int iv2=ksm(2);
int f[N][N],a[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) if(a[i]>a[j]) f[i][j]=1;
    for(int t=1;t<=m;t++)
    {
        int x,y;scanf("%d%d",&x,&y);
        f[x][y]=f[y][x]=1ll*(f[x][y]+f[y][x])*iv2%mod;
        for(int i=1;i<=n;i++) if(i!=x && i!=y) f[y][i]=f[x][i]=1ll*(f[x][i]+f[y][i])*iv2%mod,f[i][x]=f[i][y]=1ll*(f[i][x]+f[i][y])*iv2%mod;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) ans=(ans+f[i][j])%mod;
    printf("%lld ",1ll*ans*ksm(2,m)%mod);
    return 0;
}