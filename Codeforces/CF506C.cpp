#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define inf 1e16
#define ll long long
using namespace std;
ll a[N],b[N];
struct node{
    ll a,b,c;
    node(ll A=0,ll B=0,ll C=0):a(A),b(B),c(C){}
    bool operator <(const node d)const{return a==d.a?b<d.b:a>d.a;}
};
int n,k,t;ll x;
priority_queue<node>q;
bool check(ll h)
{
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++)
    if(h-a[i]<b[i]*k) q.push(node(h/b[i],i,0));
    for(int i=1;i<=k && !q.empty();i++)
        for(int j=0;j<t && !q.empty();j++)
        {
            node u=q.top();q.pop();
            if(u.a<i) return false;u.c++;
            if(h-a[u.b]+u.c*x>=b[u.b]*k) continue;
            q.push(node((h+u.c*x)/b[u.b],u.b,u.c));
        }
    return q.empty();
}
int main()
{
    scanf("%d%d%d%lld",&n,&k,&t,&x);
    ll ans=inf,l=0,r=inf;
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i],&b[i]);
    while(l<=r)
    {
        ll mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%lld\n",ans);
    return 0;
}