#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 80010
#define inf 1000000000000000000ll
#define MX 1000000000
#define ll long long
using namespace std;
struct line{
    ll k,b;
    line(ll K=0,ll B=0):k(K),b(B){}
    ll operator ()(ll x){return k*x+b;}
};
line t[N*200];int ls[N*200],rs[N*200];int tt;
void insert(int &u,int p,int l,int r,int L,int R,line v)
{
    u=++tt;
    if(p) t[u]=t[p],ls[u]=ls[p],rs[u]=rs[p];
    else t[u]=line(0,inf);
    int mid=(l+r)>>1;
    if(L<=l && r<=R)
    {
        if(t[u](mid)>v(mid)) swap(t[u],v);
        if(t[u](l)>v(l)) insert(ls[u],ls[p],l,mid,L,R,v);
        if(t[u](r)>v(r)) insert(rs[u],rs[p],mid+1,r,L,R,v);
        return;
    }
    if(L<=mid) insert(ls[u],ls[p],l,mid,L,R,v);
    if(R>mid) insert(rs[u],rs[p],mid+1,r,L,R,v);
}
ll qry(int u,int l,int r,int x)
{
    if(!u) return inf;
    if(l==r) return t[u](x);
    int mid=(l+r)>>1;
    if(x<=mid) return min(t[u](x),qry(ls[u],l,mid,x));
    else return min(t[u](x),qry(rs[u],mid+1,r,x));
}
int a[N],b[N],c[N],root[N];
vector<int>g[N];
void dfs(int u,int p)
{
    insert(root[u],root[p],0,MX,0,c[u],line(b[u],a[u]));
    for(int v:g[u]) if(v!=p) dfs(v,u);
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y),g[x].push_back(y),g[y].push_back(x);
    dfs(1,0);
    for(int i=1;i<=q;i++)
    {
        int x,t;
        scanf("%d%d",&x,&t);
        printf("%lld\n",qry(root[x],0,MX,t));
    }
    return 0;
}