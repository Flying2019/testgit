#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
#define mod 1000000007
using namespace std;
int f[2][N][N],a[N*2];//f[i][j][k]:填到 i，有 j 对填了一半的 -1,-1，k 对未匹配的 a,-1
short vis[N*2];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) scanf("%d",&a[i]);
    int tt=0;
    for(int i=1;i<=2*n;i+=2)
        if(~a[i] && ~a[i+1]) vis[a[i]]=vis[a[i+1]]=2;
        else if(~a[i] || ~a[i+1]) vis[a[i]+a[i+1]+1]=1;
        else ++tt;
    f[0][1][1]=1;
    for(int i=2*n;i;i--)if(vis[i]!=2)
    {
        swap(f[0],f[1]),memset(f[0],0,sizeof(f[0]));
        auto g=f[0];
        for(int j=1;j<=n+1;j++)
            for(int k=1;j+k<=n+2;k++)
            if(f[1][j][k])
            {
                int v=f[1][j][k];
                if(vis[i]==1) g[j-1][k]=(g[j-1][k]+v)%mod,g[j][k+1]=(g[j][k+1]+v)%mod;
                else g[j-1][k]=(g[j-1][k]+v)%mod,g[j][k-1]=(g[j][k-1]+1ll*v*(k-1))%mod,g[j+1][k]=(g[j+1][k]+v)%mod;
            }
    }
    int res=f[0][1][1];
    for(int i=1;i<=tt;i++) res=1ll*res*i%mod;
    printf("%d",res);
    return 0;
}