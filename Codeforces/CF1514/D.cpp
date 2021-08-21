#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
struct node{
    int v,c;
    node(int x=0,int y=0){v=x;c=y;}
}val[N<<2];
node operator +(node a,node b)
{
    if(a.v==b.v) return node(a.v,a.c+b.c);
    else if(a.c<b.c) return node(b.v,b.c-a.c);
    else return node(a.v,a.c-b.c);
}
int a[N];
void build(int u,int l,int r)
{
    if(l==r){val[u]=(node){a[l],1};return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid);build(u<<1|1,mid+1,r);
    val[u]=val[u<<1]+val[u<<1|1];
}
node answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;
    if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
    if(R<=mid) return answer(u<<1,l,mid,L,R);
    return answer(u<<1,l,mid,L,R)+answer(u<<1|1,mid+1,r,L,R);
}
namespace st{
    int root[N],ls[N*40],rs[N*40],val[N*40],tot;
    void insert(int &u,int l,int r,int p)
    {
        if(!u) u=++tot;val[u]++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) insert(ls[u],l,mid,p);
        else insert(rs[u],mid+1,r,p);
    }
    int answer(int u,int l,int r,int L,int R)
    {
        if(!u) return 0;
        if(L<=l && r<=R) return val[u];
        int mid=(l+r)>>1;
        if(L>mid) return answer(rs[u],mid+1,r,L,R);
        if(R<=mid) return answer(ls[u],l,mid,L,R);
        return answer(ls[u],l,mid,L,R)+answer(rs[u],mid+1,r,L,R);
    }
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),st::insert(st::root[a[i]],1,n,i);
    build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        node u=answer(1,1,n,l,r);
        int v=st::answer(st::root[u.v],1,n,l,r);
        printf("%d\n",max(v*2-(r-l+1),1));
    }
    return 0;
}