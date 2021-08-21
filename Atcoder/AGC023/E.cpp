#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=200010,mod=1000000007,iv2=(mod+1)/2;
int n;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
struct tree_a{
    int a[N];
    void clear(){memset(a,0,sizeof(a));}
    void add(int x,int v){for(;x<=n;x+=(x&-x)) a[x]=(a[x]+v)%mod;}
    int qry(int x){int v=0;for(;x;x-=(x&-x)) v=(v+a[x])%mod;return v;}
    int sum(int l,int r){return (qry(r)-qry(l-1)+mod)%mod;}
}c0,c1;
int a[N],p[N],M=1;
int pre[N],sum[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),p[a[i]]++;
    for(int i=n-1;i;i--) p[i]+=p[i+1];
    for(int i=1;i<=n;i++) p[i]-=n-i,M=1ll*M*p[i]%mod;
    sum[0]=pre[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(p[i]<=1) pre[i]=i,sum[i]=sum[i-1];
        else pre[i]=pre[i-1],sum[i]=1ll*sum[i-1]*(p[i]-1)%mod*ksm(p[i])%mod;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans+1ll*c0.sum(pre[a[i]],a[i])*sum[a[i]]%mod*iv2%mod)%mod;
        c0.add(a[i],ksm(sum[a[i]]));
    }
    c0.clear();
    for(int i=n;i;i--)
    {
        ans=(ans+c1.qry(a[i]-1)-1ll*c0.sum(pre[a[i]],a[i]-1)*sum[a[i]]%mod*iv2%mod+mod)%mod;
        c0.add(a[i],ksm(sum[a[i]]));c1.add(a[i],1);
    }
    ans=1ll*ans*M%mod;
    printf("%d\n",ans);
    return 0;
}