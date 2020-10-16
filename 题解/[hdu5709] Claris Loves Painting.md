### [链接](http://acm.hdu.edu.cn/showproblem.php?pid=5709)
考虑子树内查询相同颜色的数量，这个是一个线段树合并的经典问题。

考虑这道题，可以发现 $u$ 子树内距离 $u\leq k$ 的点的个数也可以用线段树处理。而我们将颜色的线段树合并时，相同的颜色会导致贡献-1，直接减掉即可。

于是开两棵线段树就做完了。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int ls[N*100],rs[N*100],val[N*100],rt1[N],rt2[N],tot,n;
void insert(int &pre,int l,int r,int p,int v)
{
    int u=++tot;
    val[u]=val[pre],ls[u]=ls[pre],rs[u]=rs[pre],pre=u;
    if(l==r){val[u]+=v;return;}
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls[u],l,mid,p,v);
    else insert(rs[u],mid+1,r,p,v);
    val[u]=val[ls[u]]+val[rs[u]];
}
int merge(int x,int y,int p)
{
    if(!x || !y) return x+y;
    int u=++tot;
    if(!p) val[u]=val[x]+val[y];
    else if(!ls[x] && !rs[x]) val[u]=min(val[x],val[y]),insert(rt1[p],1,n,max(val[x],val[y]),-1);
    ls[u]=merge(ls[x],ls[y],p);
    rs[u]=merge(rs[x],rs[y],p);
    return u;
}
int answer(int u,int l,int r,int L,int R)
{
    if(!u) return 0;
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1,ans=0;
    if(L<=mid) ans+=answer(ls[u],l,mid,L,R);
    if(R>mid) ans+=answer(rs[u],mid+1,r,L,R);
    return ans;
}
int dep[N],fa[N],v[N];
void dfs(int u,int p)
{
    fa[u]=p;
    dep[u]=dep[p]+1;
    insert(rt1[u],1,n,dep[u],1);
    insert(rt2[u],1,n,v[u],dep[u]);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs(v,u);
        rt1[u]=merge(rt1[u],rt1[v],0);
        rt2[u]=merge(rt2[u],rt2[v],u);
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&v[i]);
        for(int i=2;i<=n;i++) scanf("%d",&fa[i]),add(fa[i],i);
        dep[1]=1;
        dfs(1,0);
        int las=0;
        while(m --> 0)
        {
            int u,d;
            scanf("%d%d",&u,&d);
            u^=las,d^=las;
            printf("%d\n",las=answer(rt1[u],1,n,dep[u],min(dep[u]+d,n)));
        }
        for(int i=1;i<=cnt;i++) head[i]=0;
        for(int i=1;i<=n;i++) rt1[i]=rt2[i]=fa[i]=0;
        cnt=0;
        for(int i=1;i<=tot;i++) ls[i]=rs[i]=val[i]=0;
        tot=0;
    }
    return 0;
}
```
