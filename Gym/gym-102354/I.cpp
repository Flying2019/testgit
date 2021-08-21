#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 100010
#define ll long long
using namespace std;
inline ll adj(const ll &a,const ll &mod){return a>=mod?a-mod:(a<0?a+mod:a);}
inline ll mul(const ll &a,const ll &b,const ll &mod){return adj(a*b-(ll)(1.0L*a/mod*b+0.5)*mod,mod);}
inline ll ksm(ll a,ll b,ll mod)
{
    ll r=1;
    for(;b;b>>=1,a=mul(a,a,mod)) if(b&1) r=mul(r,a,mod);
    return r;
}
const int m1=1000000007,m2=1000000009,iv2=500000004;
const ll M=1ll*m1*m2,dta=1000000001;
ll c1,c2,X;
ll F(ll a,ll b,ll c,ll n)
{
    if(a>=c || b>=c) return n*(n+1)/2*(a/c)+(n+1)*(b/c)+F(a%c,b%c,c,n);
    if(n==0 || a==0) return 0;
    ll m=((__int128)a*n+b)/c;
    return n*m-F(c,c-b-1,a,m-1);
}
int main()
{
    // srand(time(0));
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        // ll p,q;
        // scanf("%lld%lld",&p,&q);
        printf("? %d\n",m1);fflush(stdout);
        scanf("%lld",&c1);/*c1=p*ksm(q,m1-2,m1)%m1;*/
        printf("? %d\n",m2);fflush(stdout);
        scanf("%lld",&c2);/*c2=p*ksm(q,m2-2,m2)%m2;*/
        X=mul((m2*c1+m1*c2)%M,iv2,M);
        // printf("%lld\n",X);
        ll l=1,r=1e9;
        while(l<r)
        {
            ll mid=(l+r)>>1;
            if(F(X,0,M,mid)!=F(X,M-dta,M,mid)-mid) r=mid;
            else l=mid+1;
        }
        // if(mul(r,X,M)>1e9){printf("%d %d\n",p,q);return 0;}
        printf("! %lld %lld\n",mul(r,X,M),r);
    }
    return 0;
}