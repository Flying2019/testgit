#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 998244353
using namespace std;
typedef long long ll;
ll a[N];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    ll m=(1ll<<k)-1,s=0,ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans+((1ll<<__builtin_popcountll(s^m))-(1ll<<__builtin_popcountll((s|a[i])^m)))%mod*i)%mod;
        s|=a[i];
    }
    printf("%lld\n",ans);
    return 0;
}