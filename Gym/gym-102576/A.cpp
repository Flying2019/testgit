#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 1000010
#define ll long long
using namespace std;
namespace min25{
    ll p[N],s[N];
    ll solve(ll n)
    {
        int S=sqrt(n),tt=0;
        auto id=[&](ll x){return x<=S?x:tt-n/x+1;};
        for(ll l=1;l<=n;l=p[tt]+1) p[++tt]=n/(n/l),s[tt]=p[tt]-1;
        for(int i=2;i<=S;i++)
        if(s[i]!=s[i-1])
        {
            ll x=1ll*i*i,q=s[i-1];
            double iv=1.0/i;
            for(int j=tt;p[j]>=x;j--) s[j]-=s[id(p[j]*iv+1e-7)]-q;
        }
        return s[tt];
    }
}
int main()
{
    int t;scanf("%d",&t);
    while(t --> 0)
    {
        ll n;
        scanf("%lld",&n);
        // printf("%lld\n",min25::solve(n));
        ll s=n-1-(min25::solve(n)-min25::solve(n/2));
        printf("%lld\n",n-s/2);
    }
    return 0;
}