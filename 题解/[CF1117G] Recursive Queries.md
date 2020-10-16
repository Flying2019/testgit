### [链接](http://codeforces.com/problemset/problem/1117/G)
显然这个式子中每个 $a_i$ 会且只会被作为最大值1次，我们不妨认为被作为最大值时额外加的部分就是 $i$ 的贡献。

可以发现，如果 $u$ 是 $[l_u,r_u]$ 中最大的。那么对于询问 $[L,R]$，$u$ 的贡献就是 $[L,R]\cap[l_u,r_u]$。

我们可以很轻松的用链表 $O(n)$ 算出 $l_i,r_i$，那么接下来就是求 $\sum_{i}{\min{(r_i,R)}}-\sum_{i}{\max{(l_i,L)}}$。

对于 $\sum_{i}{\min{(r_i,R)}}$，我们可以直接通过 $[i,r_i-1]$ 加等差数列，$[r_i,n]$ 暴力加然后单点查询得到。

对于后式同理。

然后只需要求和即可。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
struct seg_tree{
    ll val[N<<2],tag[N<<2];
    void clear(){memset(val,0,sizeof(val));memset(tag,0,sizeof(tag));}
    inline void set_tag(int u,ll v){tag[u]+=v,val[u]+=v;}
    void push_down(int u){if(tag[u]) set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]);tag[u]=0;}
    void insert(int u,int l,int r,int L,int R,ll v)
    {
        if(L<=l && r<=R){set_tag(u,v);return;}
        push_down(u);
        int mid=(l+r)>>1;
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
        val[u]=val[u<<1]+val[u<<1|1];
    }
    ll answer(int u,int l,int r,int p,int opt)
    {
        if(l==r) return val[u]*(opt==1?l:1);
        int mid=(l+r)>>1;
        push_down(u);
        if(p<=mid) return answer(u<<1,l,mid,p,opt);
        else return answer(u<<1|1,mid+1,r,p,opt);
    }
}t1,t2;
int lf[N],rf[N],a[N];
struct node{
    int l,r,id;
}q[N];
ll ans[N];
bool cmpl(node a,node b){return a.l>b.l;}
bool cmpr(node a,node b){return a.r<b.r;}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(lf[i]=i-1;lf[i] && a[i]>a[lf[i]];lf[i]=lf[lf[i]]);
    for(int i=n;i>=1;i--)
        for(rf[i]=i+1;rf[i]<=n && a[i]>a[rf[i]];rf[i]=rf[rf[i]]);
    for(int i=1;i<=n;i++) lf[i]++,rf[i]--;
    for(int i=1;i<=m;i++) scanf("%d",&q[i].l),q[i].id=i;
    for(int i=1;i<=m;i++) scanf("%d",&q[i].r);
    sort(q+1,q+m+1,cmpl);
    int u=n;
    for(int i=1;i<=m;i++)
    {
        for(;u>=q[i].l;u--)
        {
            if(u<=rf[u]-1) t1.insert(1,1,n,u,rf[u]-1,1);
            t2.insert(1,1,n,rf[u],n,rf[u]);
        }
        ans[q[i].id]=t1.answer(1,1,n,q[i].r,1)+t2.answer(1,1,n,q[i].r,2)+q[i].r-q[i].l+1;
    }
    t1.clear(),t2.clear();
    sort(q+1,q+m+1,cmpr);
    u=1;
    for(int i=1;i<=m;i++)
    {
        for(;u<=q[i].r;u++)
        {
            if(u>=lf[u]+1) t1.insert(1,1,n,lf[u]+1,u,1);
            t2.insert(1,1,n,1,lf[u],lf[u]);
        }
        ans[q[i].id]-=t1.answer(1,1,n,q[i].l,1)+t2.answer(1,1,n,q[i].l,2);
    }
    for(int i=1;i<=m;i++) printf("%lld ",ans[i]);
    return 0;
}
```
