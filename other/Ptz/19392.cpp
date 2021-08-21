#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
#include<algorithm>
#define N 200010
#define ll long long
#define lll __int128
using namespace std;
ll a[N],b[N],c[N];int n;
unordered_set<ll>st;
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
ll exgcd(ll a,ll b,lll &x,lll &y,ll x0=1)
{
    if(!b){x=x0,y=0;return a;}
    ll g=exgcd(b,a%b,y,x,x0);
    y=y-a/b*x;
    return g;
}
lll sum;
int check_id[N];
bool check0(ll mod,ll k)
{
    for(int i=1;i<=n;i++) if(!st.count((a[check_id[i]]+k)%mod)) return false;
    for(int i=1;i<=n;i++) c[i]=(a[check_id[i]]+k)%mod;
    sort(c+1,c+n+1);
    for(int i=1;i<=n;i++) if(b[i]!=c[i]) return false;
    printf("%lld %lld\n",mod,k);
    return true;
}
bool check(ll mod)
{
    if(mod<=0) return false;
    ll g=gcd(n,mod);lll x=0,y=0;
    ll s=(sum%mod+mod)%mod;
    if(s%g) return false;
    exgcd(n/g,mod/g,x,y,s/g);
    ll t=(x%mod+mod)%mod;
    for(int i=0;i<g;i++,t=(t+mod/g)%mod) if(check0(mod,(b[1]-t+mod)%mod)) return true;
    return false;
}
int main()
{
    // freopen("rand.in","r",stdin);
    srand(19260817);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]),st.insert(b[i]);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) sum+=a[i]+b[1]-b[i];
    for(int i=1;i<=n;i++) check_id[i]=i;
    random_shuffle(check_id+1,check_id+n+1);
    ll m=0;
    for(int i=1;i<=n;i++) m=max(m,b[i]);
    // printf("%lld ",m);
    for(int i=0;;i++) if(check(m+i)) return 0;
    throw;
    return 0;
}
/*
4474941420 3781144525
*/