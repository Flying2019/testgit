#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
#define ll long long
#define inf 2000000000
using namespace std;
struct node{
    int m1,m2;
    node(int M1=0,int M2=0):m1(M1),m2(M2){}
    node operator +(node a)
    {
        node b(min(m1,a.m1),min(m2,a.m2));
        if(a.m1!=b.m1) b.m2=min(b.m2,a.m1);if(m1!=b.m1) b.m2=min(b.m2,m1);
        return b;
    }
}val[N<<2];
int tag1[N<<2],tag2[N<<2],mtag1[N<<2],mtag2[N<<2],t[N<<2];
void update(int u){val[u]=val[u<<1]+val[u<<1|1];t[u]=min(t[u<<1],t[u<<1|1]);}
int a[N];
void build(int u,int l,int r)
{
    if(l==r){val[u].m1=t[u]=a[l],val[u].m2=inf;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    update(u);
}
void set_tag(int u,int v1,int v2,int m1,int m2)
{
    t[u]=min(t[u],val[u].m1+m1);
	mtag1[u]=min(mtag1[u],tag1[u]+m1);
	mtag2[u]=min(mtag2[u],tag2[u]+m2);
	tag1[u]+=v1,tag2[u]+=v2;
    val[u].m1+=v1;val[u].m2=min(val[u].m2+v2,inf);
}
void push_down(int u)
{
    if(!tag1[u] && !tag2[u] && !mtag1[u] && !mtag2[u]) return;
    int v=min(val[u<<1].m1,val[u<<1|1].m1);
    set_tag(u<<1,v==val[u<<1].m1?tag1[u]:tag2[u],tag2[u],v==val[u<<1].m1?mtag1[u]:mtag2[u],mtag2[u]);
    set_tag(u<<1|1,v==val[u<<1|1].m1?tag1[u]:tag2[u],tag2[u],v==val[u<<1|1].m1?mtag1[u]:mtag2[u],mtag2[u]);
    tag1[u]=tag2[u]=mtag1[u]=mtag2[u]=0;
}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R){set_tag(u,v,v,v,v);return;}
    int mid=(l+r)>>1;
    push_down(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
void insertm(int u,int l,int r,int L,int R,int v)
{
    if(val[u].m1>=v) return;
    if(val[u].m2>v && L<=l && r<=R){set_tag(u,v-val[u].m1,0,v-val[u].m1,0);return;}
    int mid=(l+r)>>1;
    push_down(u);
    if(L<=mid) insertm(u<<1,l,mid,L,R,v);
    if(R>mid) insertm(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
int answer(int u,int l,int r,int L,int R,int op)
{
    if(L<=l && r<=R) return op==1?val[u].m1:t[u];
    int mid=(l+r)>>1,ans=inf;
    push_down(u);
    if(L<=mid) ans=min(ans,answer(u<<1,l,mid,L,R,op));
    if(R>mid) ans=min(ans,answer(u<<1|1,mid+1,r,L,R,op));
    return ans;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r,v;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1) scanf("%d",&v),insert(1,1,n,l,r,v);
        else if(opt==2) scanf("%d",&v),insertm(1,1,n,l,r,v);
        else if(opt==3) printf("%d\n",answer(1,1,n,l,r,1));
        else if(opt==4) printf("%d\n",answer(1,1,n,l,r,0));
    }
    return 0;
}