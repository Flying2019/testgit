#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
#define M 19
using namespace std;
typedef long long ll;
int a[N],b[N];
ll f[1<<M];
ll answer(vector<int>&p)
{
    int n=p.size();
    for(int i=0;i<1<<n;i++) f[i]=0;
    ll ans=0;
    for(int i=0;i<n;i++)
        for(int s=0;s<1<<i;s++)
        {
            ll &u=f[s|(1<<i)];
            u=f[s]+a[p[i]];
            for(int j=0;j<i;j++)
            if(s>>j&1 && (i+1)%(j+1)==0) u-=b[p[i]];
            ans=max(ans,u);
        }
    return ans;
}
bool vis[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    ll ans=a[1];
    for(int i=2;i<=n;i++)
    if(!vis[i])
    {
        vector<int>p;
        for(ll j=i;j<=n;j*=i) vis[j]=true,p.push_back(j);
        ans+=answer(p);
    }
    printf("%lld\n",ans);
    return 0;
}