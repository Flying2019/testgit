#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 1000000007
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
int l[N],r[N],vl[N];
int g[N],n;
int p3(int x,int y,int z){return max(0,min(r[x],min(r[y],r[z]))-max(l[x],max(l[y],l[z])))*1ll*vl[x]%mod*vl[y]%mod*vl[z]%mod;}
int p(int x)
{
    if(x==0 || x==n) return 0;
    if(x==1) return (g[x]+g[x+1]-1)%mod;
    else return ((g[x]+g[x+1]-1)%mod+p3(x-1,x,x+1))%mod;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&l[i]);
    for(int i=1;i<=n;i++) scanf("%d",&r[i]),r[i]++;
    for(int i=1;i<=n;i++) vl[i]=ksm(r[i]-l[i]);
    int s=0;
    for(int i=1;i<=n;i++) g[i]=(1-max(0ll,(min(r[i],r[i-1])-max(l[i],l[i-1]))*1ll*vl[i]%mod*vl[i-1]%mod)+mod)%mod,s=(s+g[i])%mod;
    int ans=s;
    for(int i=1;i<=n;i++)
    {
        int r=(1ll*s-g[i]+mod-(i==1?0:g[i-1])-(i==n?0:g[i+1]))%mod;
        r=(r+mod)%mod;
        ans=(ans+1ll*g[i]*r%mod+mod)%mod;
        ans=(ans+1ll*p(i-1)+p(i))%mod;
    }
    printf("%d\n",ans);
    return 0;
}