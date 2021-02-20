#include<iostream>
#include<cstdio>
#include<cstring>
#define N 410
#define mod 998244353
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int f[N][2][N],_2[N],h[N],cnt;
int siz[N];
void solve(int &u,int l,int r,int pre)
{
    if(l>r) return ;
    int x=l;
    for(int i=l+1;i<=r;i++)
    if(h[i]<h[x]) x=i;
    u=++cnt;int ls=0,rs=0;
    solve(ls,l,x-1,h[x]);solve(rs,x+1,r,h[x]);
    auto gl=f[ls],gr=f[rs],g=f[u];
    for(int i=0;i<=siz[ls];i++)
        for(int j=0;j<=siz[rs];j++)
        {
            g[0][i+j]=(g[0][i+j]+1ll*gl[0][i]*gr[0][j])%mod;
            g[1][i+j]=(g[1][i+j]+1ll*gl[1][i]*gr[1][j]-1ll*gl[0][i]*gr[0][j]%mod+mod)%mod;
            g[0][i+j+1]=(g[0][i+j+1]-1ll*gl[0][i]*gr[0][j]%mod+mod)%mod;
            g[1][i+j+1]=(g[1][i+j+1]+1ll*gl[0][i]*gr[0][j])%mod;
        }
    siz[u]=siz[ls]+siz[rs]+1;
    for(int j=0;j<=siz[u];j++)
        g[0][j]=1ll*g[0][j]*ksm(_2[siz[u]-j],h[x]-pre)%mod,
        g[1][j]=(g[0][j]+1ll*g[1][j]*ksm(_2[siz[u]-j]-1,h[x]-pre))%mod;
}
int main()
{
    int n;
    scanf("%d",&n);
    _2[0]=f[0][0][0]=f[0][1][0]=1;
    for(int i=1;i<=n;i++) scanf("%d",&h[i]),_2[i]=_2[i-1]*2%mod;
    int u=0,ans=0;
    solve(u,1,n,0);
    for(int i=0;i<=n;i++) ans=(ans+f[u][1][i])%mod;
    printf("%d\n",ans);
    return 0;
}