#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 250010
using namespace std;
struct node{
    int u,v;
    node(int U=0,int V=0):u(U),v(V){}
};
node operator +(const node a,const node b)
{
    if(a.u==b.u) return node(a.u,a.v+b.v);
    else return a.v>b.v?node(a.u,a.v-b.v):node(b.u,b.v-a.v);
}
int siz[N],dep[N],fa[N],son[N],n;
vector<int>g[N];
void dfs(int u,int p)
{
    fa[u]=p;dep[u]=dep[p]+1;
    siz[u]=1;
    for(int v:g[u])
    if(v!=p)
    {
        dfs(v,u),siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
int id[N],dfn[N],top[N],tot;
void dfs2(int u,int topp)
{
    id[dfn[u]=++tot]=u;
    top[u]=topp;
    if(son[u]) dfs2(son[u],topp);
    for(int v:g[u]) if(v!=fa[u] && v!=son[u]) dfs2(v,v);
}
int a[N];
node val[N<<2];
void build(int u,int l,int r)
{
    if(l==r){val[u]=node(a[id[l]],1);return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    val[u]=val[u<<1]+val[u<<1|1];
}
node answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;
    if(R<=mid) return answer(u<<1,l,mid,L,R);
    if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
    return answer(u<<1,l,mid,L,R)+answer(u<<1|1,mid+1,r,L,R);
}
node answer(int x,int y)
{
    node a;
    for(;top[x]!=top[y];a=a+answer(1,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]])
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    if(dep[y]<dep[x]) swap(x,y);
    a=a+answer(1,1,n,dfn[x],dfn[y]);
    return a;
}
int lca(int x,int y)
{
    for(;top[x]!=top[y];x=fa[top[x]])
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    return dep[x]<dep[y]?x:y;
}
vector<node>qu[N];
int ans[N],ansv[N],len[N],c[N];
void dfs0(int u)
{
    c[a[u]]++;
    for(node v:qu[u]) ansv[v.u]+=v.v*c[ans[v.u]];
    for(int v:g[u]) if(v!=fa[u]) dfs0(v);
    c[a[u]]--;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        g[u].push_back(v);g[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,1);build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        ans[i]=answer(x,y).u;
        int l=lca(x,y);
        // printf("lca: %d , maxn: %d\n",l,ans[i]);
        len[i]=dep[x]+dep[y]-2*dep[l]+1;
        qu[fa[l]].push_back(node(i,-1));qu[l].push_back(node(i,-1));
        qu[x].push_back(node(i,1));qu[y].push_back(node(i,1));
    }
    dfs0(1);
    for(int i=1;i<=m;i++)
    if(ansv[i]*2>len[i]) printf("%d\n",ans[i]);
    else puts("-1");
    return 0;
}