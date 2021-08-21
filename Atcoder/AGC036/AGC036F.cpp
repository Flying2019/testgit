#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 510
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
int f[N][N],mod;
P a[N];
int main()
{
    int n;
    scanf("%d%d",&n,&mod);
    for(int i=0;i<n;i++) a[i]=MP(ceil(sqrt(n*n-i*i))-1,min((int)floor(sqrt(4*n*n-i*i)),2*n-1));
    for(int i=n;i<2*n;i++) a[i]=MP(min((int)floor(sqrt(4*n*n-i*i)),2*n-1),0);
    sort(a,a+2*n);
    int ans=0,c1=0,c2=0;
    for(int p=0;p<=n;p++)
    {
        memset(f,0,sizeof(f));
        f[0][0]=1;
        c1=0;c2=0;
        for(int i=0;i<n*2;i++)
        if(!a[i].se)
        {
            for(int j=0;j<=c2;j++) f[i+1][j]=(f[i+1][j]+1ll*f[i][j]*(a[i].fi-c1-j+1)%mod)%mod;
            c1++;
        }
        else
        {
            for(int j=0;j<=c2;j++) f[i+1][j]=(f[i+1][j]+1ll*f[i][j]*(a[i].se-c2+j-n-p+1))%mod;
            for(int j=0;j<=c2;j++) f[i+1][j+1]=(f[i+1][j+1]+1ll*f[i][j]*(a[i].fi-c1-j+1))%mod;
            c2++;
        }
        ans=(ans+(p&1?mod-1ll:1ll)*f[n*2][p])%mod;
    }
    printf("%d\n",ans);
    return 0;
}