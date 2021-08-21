#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define mod 1000000007
using namespace std;
int f[N],p[N],s[N],g[N][N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod)
    if(b&1) r=1ll*r*a%mod;
    return r;
}
int main()
{
    int n,k=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]),f[i]=i;
    for(int i=1;i<=n;i++)
    if(p[i]!=-1) f[find(i)]=find(p[i]);
    for(int i=1;i<=n;i++) s[find(i)]++;
    int tt=0;
    for(int i=1;i<=n;i++)
    if(p[i]!=-1 && s[i]) tt++;
    int ans=0;g[0][0]=1;
    for(int i=1;i<=n;i++)
    if(p[i]==-1)
    {
        ++k;
        for(int j=0;j<=k;j++) g[k][j]=g[k-1][j];
        for(int j=1;j<=k;j++) g[k][j]=(g[k-1][j]+1ll*g[k-1][j-1]*s[i]%mod*max(1,j-1)%mod)%mod;
    }
    for(int i=1;i<=n;i++)
    if(p[i]==-1) ans=(ans+1ll*(s[i]-1)*ksm(n-1,k-1))%mod;
    for(int i=2;i<=k;i++) ans=(ans+1ll*g[k][i]*ksm(n-1,k-i))%mod;
    printf("%d\n",(1ll*(n-tt)*ksm(n-1,k)%mod-ans+mod)%mod);
    return 0;
}