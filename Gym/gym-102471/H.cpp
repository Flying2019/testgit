#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 200010
using namespace std;
int mod;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int a[N],b[N];
map<int,int>mp;
int f[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T --> 0)
    {
        mp.clear();
        int n;
        scanf("%d%d",&n,&mod);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=ksm(a[i]);
        for(int i=1;i<n;i++) mp[1ll*a[i+1]*b[i]%mod]++;
        for(int i=1;i<n-1;i++) mp[1ll*a[i+2]*b[i]%mod]++;
        int ans=0;
        for(auto s:mp)
        {
            if(s.second<n/4-1) continue;
            int x=ksm(s.first);
            map<int,int>g;f[0]=0;
            int res=1;
            for(int i=1;i<=n;i++)
            if(g.count(1ll*a[i]*x%mod)) f[i]=f[g[1ll*a[i]*x%mod]]+1,g[a[i]]=i,res=max(res,f[i]);
            else f[i]=1,g[a[i]]=i;
            ans=max(ans,res);
        }
        printf("%d\n",ans>=(n+1)/2?ans:-1);
    }
    return 0;
}