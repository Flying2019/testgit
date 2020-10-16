### [����](http://115.236.49.52:83/contest/1600/problem/1)
���ȿ��Է��֣����� $(d,m)\neq 1$����ô���λ�ò���Դ�����κι��ס�

���� $(d,m)=1$����ô $d$ �Ĵ�СҲ����Դ����Ӱ�졣

������·�����ǽ� $[l,r]$ ���� $[1,r]-[1,l-1]$���� $[1,x]$ ���� $m$ ���ʵ����ֵĸ�����һ���������⡣�� $m$ �������Ӵ������������Щ�����ӽ����ݳ⼴�ɡ����� $10^9$ ���ֻ��8�������ӣ����Ը��Ӷ� $O(2^8)$��

���������Ǵ�����֮����ظ�����Ȼ $A+B-A\cap B=A\cup B$���������� $A\cap B$ ��ʽ��Ҳ��һ�� $[l,r]\times d$ ����ʽ��

��������ֱ�Ӵ���������Ӽ� $S$ �еĽ�����Ϣ���Ӽ�dp���ɡ����Ӷ� $O(2^n\times n)$��

������ʱ�临�Ӷ� $O(2^nn+2^{n+8})$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
#define int long long
#define ll long long
using namespace std;
int p[13],tot;
ll f[1<<13];
struct node{
    ll l,r,d;
    node(ll L=0,ll R=0,ll D=0):l(L),r(R),d(D){}
}q[20];
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
ll work(ll x)
{
    ll ans=0;
    for(int i=0;i<(1<<tot);i++)
        ans+=((__builtin_popcount(i)&1)?-1ll:1ll)*(x/f[i]);
    return ans;
}
node merge(node a,node b)
{
    if(a.d==0 || b.d==0) return node(0,0,0);
    ll c=gcd(a.d,b.d);
    if(b.d/c<=a.r&&a.d/c<=b.r)
    {
        ll l1=a.l/(b.d/c),l2=b.l/(a.d/c);
        if(a.l%(b.d/c)) ++l1;
        if(b.l%(a.d/c)) ++l2;
        ll r1=a.r/(b.d/c),r2=b.r/(a.d/c);
        if(max(l1,l2)>min(r1,r2)) return node(0,0,0);
        return node(max(l1,l2),min(r1,r2),a.d/c*b.d);
    }
    return node(0,0,0);
}
node g[1<<17];
bool prime[N];
int prm[N],ptot;
void pre(int n)
{
    for(int i=2;i<=n;i++)
    if(!prime[i])
    {
        prm[++ptot]=i;
        for(int j=2;1ll*i*j<=n;j++) prime[1ll*i*j]=true;
    }
}
signed main()
{
    int n,m;
    scanf("%lld%lld",&n,&m);
    int m1=m;
    pre(N-10);
    for(int i=1;i<=ptot && prm[i]<=m;i++)
    if(m%prm[i]==0){p[tot++]=prm[i];while(m%prm[i]==0) m/=prm[i];}
    if(m!=1) p[tot++]=m,m=1;
    int t=1<<tot;
    for(int i=0;i<t;i++)
    {
        f[i]=1;
        for(int j=0;j<tot;j++)
        if((i>>j)&1) f[i]=f[i]*p[j];
    }
    for(int i=0;i<n;i++) scanf("%lld%lld%lld",&q[i].l,&q[i].r,&q[i].d);
    int tn=0;
    for(int i=0;i<n;i++)
    if(gcd(m1,q[i].d)==1) q[tn++]=q[i];
    n=tn;
    for(int i=0;i<n;i++) g[1<<i]=q[i];
    for(int i=1;i<1<<n;i++)
        for(int j=0;j<n;j++)
        if(!(i&(1<<j)) && g[i|(1<<j)].d==0) g[i|(1<<j)]=merge(g[i],g[1<<j]);
    ll ans=0;
    for(int i=1;i<1<<n;i++)
    if(g[i].d) ans+=((__builtin_popcount(i)&1)?1ll:-1ll)*(work(g[i].r)-work(g[i].l-1));
    // print(ans);
    printf("%lld\n",ans);
    return 0;
}
```
