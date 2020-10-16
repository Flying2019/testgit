### [链接](http://115.236.49.52:83/contest/1579)
首先考虑没有修改 ($q=0$) 的情况，显然就是 [AGC038C](https://www.cnblogs.com/Flying2018/p/13493250.html)。

考虑修改。首先区间赋值想到的就是ODT，可以发现，我们只需要能维护把某种 $a_i$ 的值的个数减少/加上 $v$ 个即可。

可以发现对于一个 $a_i$，它修改后会影响的范围其实是它的因子。又因为因子个数是 $O(\sqrt{n})$ 的，所以直接暴力维护即可。

复杂度 $O(m\sqrt{n}+m\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define int long long
#define N 1000010
#define mod 998244353
#define inv2 ((mod+1)/2)
using namespace std;
int mu[N],pr[N],tot;
int f[N],g[N],cnt[N];
bool p[N];
void pre(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) pr[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot && i*pr[j]<=n;j++)
        {
            p[i*pr[j]]=1;
            if(i%pr[j]==0){mu[i*pr[j]]=0;break;}
            mu[i*pr[j]]=mod-mu[i];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;1ll*i*j<=n;j++)
        f[i*j]=(f[i*j]+1ll*i*mu[i]%mod+mod)%mod;
    }
}
int ans,a[N];
void update(int i,int t,int v,int p)
{
    ans=(ans-1ll*f[i]*i%mod*g[i]%mod*g[i]%mod+mod)%mod;
    g[i]=(g[i]-1ll*t*p%mod+mod)%mod;
    g[i]=(g[i]+1ll*v*p%mod)%mod;
    ans=(ans+1ll*f[i]*i%mod*g[i]%mod*g[i]%mod+mod)%mod;
}
void change(int x,int v)
{
    for(int i=1;i*i<=x;i++)
    if(x%i==0)
    {
        update(i,cnt[i],cnt[i]+v,x/i);
        if(i*i!=x) update(x/i,cnt[x/i],cnt[x/i]+v,x/(x/i));
    }
    cnt[x]+=v;
}
struct ODT{
    struct node{
        int l,r;
        mutable int v;
        bool operator <(const node &a)const{return l<a.l;}
        node(int L=0,int R=0,int V=0):l(L),r(R),v(V){}
    };
    set<node>s;
    #define It set<node>::iterator
    It split(int x)
    {
        It p=s.lower_bound(node(x));
        if(p!=s.end() && p->l==x) return p;
        --p;
		int l=p->l,r=p->r,v=p->v;
        s.erase(p);
		s.insert(node(l,x-1,v));
        return s.insert(node(x,r,v)).first;
    }
    void init(int a[],int n)
    {
        for(int i=1;i<=n;i++)
        s.insert(node(i,i,a[i]));
    }
    void insert(int l,int r,int v)
    {
        It rr=split(r+1),ll=split(l);
        for(It i=ll;i!=rr;i++)
        {
            int lf=i->l,rf=i->r,vf=i->v;
            change(vf,-(rf-lf+1));
        }
        s.erase(ll,rr);
        s.insert(node(l,r,v));
        change(v,r-l+1);
    }
}t;
signed main()
{
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    int n,m=0,q;
    scanf("%*d%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        cnt[a[i]]++;
        m=max(m,a[i]);
    }
    scanf("%lld",&q);
    pre(N-10);
    for(int i=1;i<=N-10;i++)
    {
        for(int j=1;1ll*i*j<=N-10;j++)
            g[i]=(g[i]+1ll*cnt[i*j]*j%mod)%mod;
        ans=(ans+1ll*f[i]*i%mod*g[i]%mod*g[i]%mod)%mod;
    }
    printf("%lld\n",ans);
    t.init(a,n);
    while(q --> 0)
    {
        int l,r,v;
        scanf("%lld%lld%lld",&l,&r,&v);
        t.insert(l,r,v);
        printf("%lld\n",ans);
    }
    return 0;
}
```
