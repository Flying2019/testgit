#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
#define ll long long
using namespace std;
ll calc(ll x){return x>1e9?1e18+5:(3*x*x-x)/2;}
ll calc2(ll x){return x>1e9?1e18+5:(3*x*x+x)/2;}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        ll n;
        scanf("%lld",&n);
        long long x=0;
        for(int k=31;~k;k--) if(calc(x+(1ll<<k))<n) x+=1ll<<k;
        x++;
        if(calc(x)==n) printf("%d ",x&1?8:1);
        else
        {
            ll y=0;
            for(int k=31;~k;k--) if(calc2(y+(1ll<<k))<n) y+=1ll<<k;
            printf("%d ",y&1?0:9);
        }
    }
    return 0;
}