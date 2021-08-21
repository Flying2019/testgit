#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=200010;
struct node{
    int v;bool l,r;
    node(int V=0,int L=0,int R=0):v(V),l(L),r(R){}
};
node operator +(const node a,const node b){return node(a.v+b.v-(a.r==b.l),a.l,b.r);}
struct tree{
    node t[N<<2];
    void build(int u,int l,int r,int a[])
    {
        if(l==r){t[u]=node(1,a[l],a[l]);return;}
        int mid=(l+r)>>1;
        build(u<<1,l,mid,a);build(u<<1|1,mid+1,r,a);
        t[u]=t[u<<1]+t[u<<1|1];
    }
    node qry(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return t[u];
        int mid=(l+r)>>1;
        if(R<=mid) return qry(u<<1,l,mid,L,R);
        if(L>mid) return qry(u<<1|1,mid+1,r,L,R);
        return qry(u<<1,l,mid,L,R)+qry(u<<1|1,mid+1,r,L,R);
    }
}t1,t2;
int a[N],b[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[n+i]=a[i];
    for(int i=1;i<=m;i++) scanf("%d",&b[i]),b[m+i]=b[i];
    t1.build(1,1,n*2,a);
    t2.build(1,1,m*2,b);
    int q;scanf("%d",&q);
    while(q --> 0)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1>x2) swap(x1,x2);if(y1>y2) swap(y1,y2);
        int res=min(t1.qry(1,1,n*2,x1,x2).v,t1.qry(1,1,n*2,x2,x1+n).v)-1;
        res+=min(t2.qry(1,1,m*2,y1,y2).v,t2.qry(1,1,m*2,y2,y1+m).v)-1;
        printf("%d\n",res);
    }
    return 0;
}