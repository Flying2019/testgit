#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 110
#define ll long long
using namespace std;
const ll mod=411191981019260843;
ll mul(ll a,ll b){return ((a*b-(ll)((long double)a/mod*b+0.5)*mod)%mod+mod)%mod;}
ll ksm(ll a,ll b=(mod+1)/4)
{
    ll r=1;
    for(;b;b>>=1,a=mul(a,a)) if(b&1) r=mul(r,a);
    return r;
}
ll read()
{
    int ch=0;ll x=0;
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) x=(x*10+ch-'0')%mod,ch=getchar();
    return x;
}
ll a[N];
map<ll,int>st;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) a[i]=ksm(read());
    // for(int i=0;i<n;i++) printf("%lld\n",a[i]);
    int m=n/2;n-=m;
    for(int s=0;s<1<<m;s++)
    {
        ll x=0;
        for(int i=0;i<m;i++) if(s>>i&1) x=(x+a[i])%mod;else x=(x-a[i])%mod;
        st[(mod-x)%mod]++;
    }
    ll ans=0;
    for(int s=0;s<1<<n;s++)
    {
        ll x=0;
        for(int i=0;i<n;i++) if(s>>i&1) x=(x+a[m+i])%mod;else x=(x-a[m+i])%mod;
        x=(x+mod)%mod;
        if(st.count(x)) ans+=st[x];
    }
    printf("%lld\n",ans/2);
    return 0;
}