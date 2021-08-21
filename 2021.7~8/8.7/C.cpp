#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
ll sq(ll x){return x*x;}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        ll n,m,x1,x2;scanf("%lld%lld%lld%lld",&n,&m,&x1,&x2);
        ll t=min(sq(x1-1),sq(m-x2));
        t=min(t,sq(n-1));
        t=min(t,sq((abs(x1-x2)+n-2+(x1==x2))/2));
        printf("%lld\n",t);
    }
    return 0;
}