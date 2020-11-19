#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#define N 200010
#define B 220
#define BL (N/B+2)
#define ll long long
#define ull unsigned long long
#define inf 1e18
using namespace std;
struct line{
    ll k,b;
    line(ll K=0,ll b1=0):k(K),b(b1){}
    bool operator <(const line a)const{return k<a.k;}
    line operator -(void){return line(k,-b);}
};
inline bool cmp(line a,line b,line c)
{
    // if(1.0f*(b.b-c.b)*(b.k-a.k)<=2e18f ^ 1.0f*(a.b-b.b)*(c.k-b.k)<=2e18f) return 1.0f*(b.b-c.b)*(b.k-a.k)>2e18f;
    return ((long double)(b.b-c.b)*(b.k-a.k)<=(long double)(a.b-b.b)*(c.k-b.k));
}
inline ll X(line a,ll x){return a.k*x+a.b;}
struct convex{
    vector<line>v;
    void insert(line x)
    {
        int p=v.size();
        for(--p;p>0 && cmp(v[p-1],v[p],x);--p,v.pop_back());
        v.push_back(x);
    }
    ll qry(ll x)
    {
        if(v.empty()) return -inf;
        int l=0,r=v.size()-1;
        while(l<r)
        {
            int m=(l+r)>>1;
            if(X(v[m],x)<=X(v[m+1],x)) l=m+1;
            else r=m;
        }
        return X(v[l],x);
    }
};
vector<line>s;
ll a[N],b[N];
struct block{
    convex f,g;
    int l,r;ll tag;
    block(){l=1e8;}
    void build()
    {
        s.clear();f.v.clear();g.v.clear();
        for(int i=l;i<=r;i++) a[i]+=tag,s.push_back(line(b[i],a[i]*b[i]));tag=0;
        sort(s.begin(),s.end());
        for(auto u:s) f.insert(u);
        for(auto u:s) g.insert(-u);
    }
    ll qry(){return max(f.qry(tag),g.qry(-tag));}
    void upd(int l0,int r0,ll val){for(int i=l0;i<=r0;i++) a[i]=a[i]+val;build();}
    ll qry(int l0,int r0){ll ans=0;for(int i=l0;i<=r0;i++) ans=max(ans,llabs(a[i]+tag)*b[i]);return ans;}
}c[BL];
int bl[N],fa[N];
vector<int>g[N];
int l[N],r[N],nid;
ll ta[N],tb[N];
void dfs(int u)
{
    l[u]=++nid;
    for(int v:g[u]) ta[v]+=ta[u],tb[v]+=tb[u],dfs(v);
    r[u]=nid;
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++) scanf("%d",&fa[i]),g[fa[i]].push_back(i);
    for(int i=1;i<=n;i++) scanf("%lld",&ta[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&tb[i]);
    dfs(1);
    for(int i=1;i<=n;i++) a[l[i]]=ta[i],b[l[i]]=llabs(tb[i]);
    for(int i=1;i<=n;i++) bl[i]=i/B,c[bl[i]].l=min(c[bl[i]].l,i),c[bl[i]].r=max(c[bl[i]].r,i);
    int m=bl[n];
    for(int i=0;i<=m;i++) c[i].build();
    while(q --> 0)
    {
        int opt,x;ll y;
        scanf("%d%d",&opt,&x);
        if(opt==1)
        {
            scanf("%lld",&y);
            int fl=bl[l[x]],fr=bl[r[x]];
            if(fl==fr) c[fl].upd(l[x],r[x],y);
            else
            {
                c[fl].upd(l[x],c[fl].r,y);
                c[fr].upd(c[fr].l,r[x],y);
                for(int i=fl+1;i<fr;i++) c[i].tag+=y;
            }
        }
        else
        {
            int fl=bl[l[x]],fr=bl[r[x]];
            if(fl==fr) printf("%lld\n",c[fl].qry(l[x],r[x]));
            else
            {
                ll ans=max(c[fl].qry(l[x],c[fl].r),c[fr].qry(c[fr].l,r[x]));
                for(int i=fl+1;i<fr;i++) ans=max(ans,c[i].qry());
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}