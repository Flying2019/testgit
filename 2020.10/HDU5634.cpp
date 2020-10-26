#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#define M 10000010
#define ll long long
using namespace std;
int a[N];
int ph[M],p[M],tot;
bool pm[M];
void pre_work(int n)
{
    ph[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pm[i]) p[++tot]=i,ph[i]=i-1;
        for(int j=1;j<=tot && i*p[j]<=n;j++)
        {
            pm[i*p[j]]=true;
            if(i%p[j]==0){ph[i*p[j]]=ph[i]*p[j];break;}
            else ph[i*p[j]]=ph[i]*(p[j]-1);
        }
    }
}
ll val[N<<2];
int tv[N<<2],tag[N<<2];
void update(int u){val[u]=val[u<<1]+val[u<<1|1];tv[u]=(tv[u<<1]==tv[u<<1|1]?tv[u<<1]:0);}
void set_tag(int u,int l,int r,int v){tag[u]=tv[u]=v;val[u]=(ll)v*(r-l+1);}
void push_down(int u,int l,int r)
{
    if(!tag[u]) return;
    int mid=(l+r)>>1;
    set_tag(u<<1,l,mid,tag[u]),set_tag(u<<1|1,mid+1,r,tag[u]);
    tag[u]=0;
}
void build(int u,int l,int r)
{
    tag[u]=0;tv[u]=0;
    if(l==r){val[u]=tv[u]=a[l];return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    update(u);
}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R)
    {
        if(v>0){set_tag(u,l,r,v);return;}
        if(tv[u]){set_tag(u,l,r,ph[tv[u]]);return;}
    }
    push_down(u,l,r);
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
ll answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;
    ll ans=0;
    push_down(u,l,r);
    if(L<=mid) ans=answer(u<<1,l,mid,L,R);
    if(R>mid) ans+=answer(u<<1|1,mid+1,r,L,R);
    return ans;
}
int main()
{
    int t;
    scanf("%d",&t);
    pre_work(M-10);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        build(1,1,n);
        while(m --> 0)
        {
            int op,l,r,x;
            scanf("%d%d%d",&op,&l,&r);
            if(op==1) insert(1,1,n,l,r,-1);
            else if(op==2) scanf("%d",&x),insert(1,1,n,l,r,x);
            else printf("%lld\n",answer(1,1,n,l,r));
        }
    }
    return 0;
}