#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
#define ll long long
using namespace std;
pair<ll,ll> fen(ll n)
{
    int t=sqrt(n);
    for(int i=t;;i++) if(n%i==0) return make_pair(i,n/i);
    exit(2333);
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1,y=0;return x;}
    ll t=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return t;
}
ll mul(ll a,ll b,ll mod){return (a*b-(ll)((long double)a*b/mod)*mod+mod)%mod;}
ll ksm(ll a,ll b,ll mod)
{
    ll r=1;
    for(;b;b>>=1,a=mul(a,a,mod)) if(b&1) r=mul(r,a,mod);
    return r;
}
const int e=(1<<30)+3;
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        ll n,c;
        scanf("%lld%lld",&n,&c);
        auto p=fen(n);ll r=(p.first-1)*(p.second-1);
        ll ex=0,ey=0;
        exgcd(e,r,ex,ey);
        ex=(ex%r+r)%r;
        printf("Case %d: ",_);
        printf("%lld\n",ksm(c,ex,n));
    }
    return 0;
}