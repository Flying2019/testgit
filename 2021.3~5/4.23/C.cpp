#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
#define M N*20
using namespace std;
namespace fhq_treap{
    struct node{
        int v,c;
        node(int V=0,int C=0):v(V),c(C){}
    };
    node operator +(const node a,int b){return node(a.v+b,a.c);}
    bool operator <(const node a,const node b){return a.v==b.v?a.c<b.c:a.v<b.v;}
    int ls[M],rs[M],siz[M],tag[M],rnd[M];
    ll sum[M];node val[M];
    int tot;
    void update(int u)
    {
        siz[u]=siz[ls[u]]+siz[rs[u]]+1;
        sum[u]=sum[ls[u]]+sum[rs[u]]+val[u].v;
    }
    void setg(int u,int v)
    {
        if(!u) return;
        tag[u]+=v;sum[u]+=1ll*v*siz[u];
    }
    void push(int u){if(tag[u]) setg(ls[u],tag[u]),setg(rs[u],tag[u]),tag[u]=0;}
    int new_node(node v)
    {
        val[++tot]=v;sum[tot]=v.v;siz[tot]=1;rnd[tot]=rand();
        return tot;
    }
    int merge(int x,int y)
    {
        if(!x || !y) return x+y;
        push(x);push(y);
        if(rnd[x]<rnd[y])
        {
            rs[x]=merge(rs[x],y);update(x);
            return x;
        }
        else
        {
            ls[y]=merge(x,ls[y]);update(y);
            return y;
        }
    }
    void split(int u,node k,int &lt,int &rt)
    {
        if(!u){lt=rt=0;return;}
        push(u);
        if(val[u]<k) lt=u, split(rs[u],k,rs[u],rt);
        else rt=u, split(ls[u],k,lt,ls[u]);
        update(u);
    }
}
using fhq_treap::node;
using fhq_treap::new_node;
using fhq_treap::merge;
using fhq_treap::split;
int root[N<<2],a[N],tag[N],m;
void setg(int u,int v)
{
    v%=m;
    tag[u]+=v;tag[u]%=m;
    fhq_treap::setg(root[u],v);
    int rt=0;split(root[u],node(m,-1),root[u],rt);
    fhq_treap::setg(rt,-m);
    root[u]=merge(rt,root[u]);
}
void push(int u){if(tag[u]) setg(u<<1,tag[u]),setg(u<<1|1,tag[u]),tag[u]=0;}
void build(int u,int l,int r)
{
    vector<node>s;s.reserve(r-l+1);
    for(int i=l;i<=r;i++) s.push_back(node(a[i],l));
    sort(s.begin(),s.end());
    for(node v:s) root[u]=merge(root[u],new_node(v));
    if(l==r) return;
    int mid=(l+r)>>1;
    build(u<<1,l,mid);build(u<<1|1,mid+1,r);
}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R){setg(u,v);return;}
    push(u);
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
}
ll answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return fhq_treap::sum[root[u]];
    push(u);
    int mid=(l+r)>>1;ll res=0;
    if(L<=mid) res+=answer(u<<1,l,mid,L,R);
    if(R>mid) res+=answer(u<<1|1,mid+1,r,L,R);
    return res;
}
int main()
{
    int n,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    while(q --> 0)
    {
        int op,l,r,v;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) scanf("%d",&v),insert(1,1,n,l,r,v);
        else printf("%lld\n",answer(1,1,n,l,r));
    }
    return 0;
}