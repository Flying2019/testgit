#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
#define ll long long
#define inf 1000000000000000000ll
using namespace std;
struct node{
    ll a,m;//max(x+a,m)
    node(ll A=0,ll B=-inf):a(A),m(B){}
    node operator +(const node b)const{return node(max(-inf,a+b.a),max(m+b.a,b.m));}
    node operator *(const node b)const{return node(max(a,b.a),max(m,b.m));}
}tu[N<<2],th[N<<2];
ll mu[N<<2],mh[N<<2],a[N];
void update(int u){mu[u]=max(mu[u<<1],mu[u<<1|1]);mh[u]=max(mh[u<<1],mh[u<<1|1]);}
void build(int u,int l,int r)
{
    if(l==r){mu[u]=mh[u]=a[l];return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    update(u);
}
void set_tag(int u,node v,node h)
{
    th[u]=th[u]*(tu[u]+h);
    tu[u]=tu[u]+v;
    mh[u]=max(mh[u],max(mu[u]+h.a,h.m));
    mu[u]=max(mu[u]+v.a,v.m);
}
void push_down(int u)
{
    set_tag(u<<1,tu[u],th[u]),set_tag(u<<1|1,tu[u],th[u]);
    tu[u]=th[u]=node();
}
void insert(int u,int l,int r,int L,int R,node v)
{
    if(L<=l && r<=R){set_tag(u,v,v);return;}
    int mid=(l+r)>>1;
    push_down(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
ll answer(int u,int l,int r,int p,int x)
{
    if(l==r) return x==4?mu[u]:mh[u];
    int mid=(l+r)>>1;
    push_down(u);
    if(p<=mid) return answer(u<<1,l,mid,p,x);
    else return answer(u<<1|1,mid+1,r,p,x);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op,l,r;
        ll x;
        scanf("%d%d",&op,&l);
        if(op==1) scanf("%d%lld",&r,&x),insert(1,1,n,l,r,node(x,-inf));
        else if(op==2) scanf("%d%lld",&r,&x),insert(1,1,n,l,r,node(-x,0));
        else if(op==3) scanf("%d%lld",&r,&x),insert(1,1,n,l,r,node(-inf,x));
		else printf("%lld\n",answer(1,1,n,l,op));
    }
    return 0;
}