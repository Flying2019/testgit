#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
#define ll long long
using namespace std;
int a[N];
ll val[N<<2],tag[N<<2],mx[N<<2],mn[N<<2];
void update(int u,int l,int r)
{
    val[u]=val[u<<1]+val[u<<1|1]+tag[u]*(r-l+1);
    mx[u]=max(mx[u<<1],mx[u<<1|1])+tag[u];
    mn[u]=min(mn[u<<1],mn[u<<1|1])+tag[u];
}
void build(int u,int l,int r,int a[])
{
    if(l==r){val[u]=mx[u]=mn[u]=a[l];return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid,a),build(u<<1|1,mid+1,r,a);
    update(u,l,r);
}
void set_tag(int u,ll v,int l,int r){tag[u]+=v;val[u]+=v*(r-l+1);mn[u]+=v;mx[u]+=v;}
void change(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R){set_tag(u,v,l,r);return;}
    int mid=(l+r)>>1;
    if(L<=mid) change(u<<1,l,mid,L,R,v);
    if(R>mid) change(u<<1|1,mid+1,r,L,R,v);
    update(u,l,r);
}
void push_down(int u,int l,int r)
{
    if(!tag[u]) return;
    int mid=(l+r)>>1;
    set_tag(u<<1,tag[u],l,mid);set_tag(u<<1|1,tag[u],mid+1,r);
    tag[u]=0;
}
void csqrt(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R)
        if(mx[u]==mn[u] || (mx[u]==mn[u]+1 && (ll)sqrt(mn[u])+1==(ll)sqrt(mx[u]))){set_tag(u,(ll)sqrt(mn[u])-mn[u],l,r);return ;}
    int mid=(l+r)>>1;
    push_down(u,l,r);
    if(L<=mid) csqrt(u<<1,l,mid,L,R);
    if(R>mid) csqrt(u<<1|1,mid+1,r,L,R);
    update(u,l,r);
}
ll answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;ll ans=0;
    push_down(u,l,r);
    if(L<=mid) ans+=answer(u<<1,l,mid,L,R);
    if(R>mid) ans+=answer(u<<1|1,mid+1,r,L,R);
    return ans;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n,a);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r,x;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1) scanf("%d",&x),change(1,1,n,l,r,x);
        else if(opt==2) csqrt(1,1,n,l,r);
        else printf("%lld\n",answer(1,1,n,l,r));
    }
    return 0;
}