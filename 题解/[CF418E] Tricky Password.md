### [链接](http://codeforces.com/problemset/problem/418/E)
### 题目大意
给定 $f_{1,i}$，令 $f_{i,j}$ 等于 $f_{i-1,j} $ 在 $f_{i-1,k}\ ,\ 1\leq k\leq j$ 中出现的次数。

动态修改 $f_{1,i}$，查询 $f_{i,j}$。$n,q\leq 10^5$。
### 题解
首先考虑行数非常的大，所以考虑打表发现对于 $i\geq 4$，$f_{i,j}=f_{i-2,j}$。

考虑如何证明：由于 $f_{3,i}$ 是 $f_{2,i}$ 在 $f_{2,[1,i]}$ 中的出现次数。显然有 $f_{3,1}=1$。

将 $f_{3}$ 中的每一种数字数字分为一种，按位置排序后可以发现他们变换后的值分别是 $1,2,3,\cdots$。

再次处理 $f_4$，可以发现对于 $f_2$ 每一种数字的第一位按位置排序后分别是 $1,2,3,\cdots$。

由于 $f_2$ 是由 $f_1$ 变换得到，可以发现 $f_2$ 是由若干递增序列 $1,2,3\cdots$ 插入得到。所以 $f_4=f_2$。显然有 $f_x=f_{x-2}$。

所以接下来问题变成如何动态求 $f_x$。考虑对于 $x=2k$ 的情况，显然就是 $f_1$ 一次变换得到直接用线段树（树状数组）维护当前数字 $u$ 在所有 $f_{1,i}=u$ 的出现位置。

那么如何求 $x=2k+1$ 的情况。首先 $x=1$ 显然需要特判。否则有 $f_{x}=f_3$。

可以发现，这里 $f_{3,y}$ 的本质是求 $f_{1,[1,y]}$ 中某一数字 $k$ 对应的集合大小 $|S_k|\geq$ $y$ 所在集合的集合大小 $|S_y|$ 的 $k$ 的个数。

显然需要离线，用 $(k,t)$ 表示在 $t$ 时间查询 $f_{3,k}$。可以发现对于某个询问 $(k,t)$，只有 $x\leq k$ 的点和 $(x\leq k,\ y\leq t)$ 的修改会产生贡献。

这就是一个经典的弱化版的莫队了。考虑将询问先按 $k$ 的区块排序，再按 $t$ 排序。对于每个区块，将时间 $T$ 从 1 推到 $q$ ，然后对于每次 $T=t_i$ 时，暴力移动右端点，加入/删除对应的点。对于修改修改同理，用一个树状数组维护所有数字集合的出现次数的前缀和即可。（~~线段树好像会T~~）

复杂度 $O(n\sqrt n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define N 200010
#define M N*40
using namespace std;
int root[N],siz[M],ls[M],rs[M],cnt;
void insert(int &u,int l,int r,int p,int v)
{
    if(!u) u=++cnt;
    if(l==r){siz[u]+=v;return;}
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls[u],l,mid,p,v);
    else insert(rs[u],mid+1,r,p,v);
    siz[u]=siz[ls[u]]+siz[rs[u]];
}
int answer(int u,int l,int r,int p)
{
    if(!u) return 0;
    if(l==r) return siz[u];
    int mid=(l+r)>>1;
    if(p<=mid) return answer(ls[u],l,mid,p);
    else return siz[ls[u]]+answer(rs[u],mid+1,r,p);
}
int answerb(int u,int l,int r,int p)
{
    if(!u) return 0;
    if(l==r) return siz[u];
    int mid=(l+r)>>1;
    if(p>mid) return answerb(rs[u],mid+1,r,p);
    else return siz[rs[u]]+answerb(ls[u],l,mid,p);
}
#define B 800
int bl[N*2];
struct Opt{
    int opt,x,y,id;
}q[N];
struct odpt{
    int t,y;
}qt[N];
bool operator <(const odpt a,const odpt b){return bl[a.y]==bl[b.y]?a.t<b.t:bl[a.y]<bl[b.y];}
int qtot;
int w[N],p[N*2],tto;
int swp[N],ans[N],tot[N];
int tval[N];
int lowbit(int x){return x&(-x);}
void t_insert(int x,int v){for(;x;x-=lowbit(x)) tval[x]+=v;}
int t_answer(int n,int x){int ans=0;for(;x<=n;x+=lowbit(x)) ans+=tval[x];return ans;}
void change(int n,int x,int y)
{
    if(x)
    {
        t_insert(tot[x],-1);
        tot[x]--;
        t_insert(tot[x],1);
    }
    if(y)
    {
        t_insert(tot[y],-1);
        tot[y]++;
        t_insert(tot[y],1);
    }
}
int main()
{
    int n,k;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]),p[++tto]=w[i];
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d%d",&q[i].opt,&q[i].x,&q[i].y);
        q[i].id=i;
        if(q[i].opt==1) p[++tto]=q[i].x;
    }
    sort(p+1,p+tto+1);
    tto=unique(p+1,p+tto+1)-p-1;
    for(int i=1;i<=n;i++) w[i]=lower_bound(p+1,p+tto+1,w[i])-p;
    for(int i=1;i<=k;i++)
        if(q[i].opt==1) q[i].x=lower_bound(p+1,p+tto+1,q[i].x)-p;
    for(int i=1;i<=n;i++) insert(root[w[i]],1,n,i,1),swp[i]=w[i];
    for(int i=1;i<=k;i++)
    if((q[i].opt==2 && q[i].x%2==1 && q[i].x!=1))
    {
        ++qtot;
        qt[qtot]=(odpt){i,q[i].y};
    }
    for(int i=1;i<=n;i++) bl[i]=i/B;
    sort(qt+1,qt+qtot+1);
    for(int i=1;i<=k;i++)
    {
        int x=q[i].x,y=q[i].y;
        if(q[i].opt==2)
        {
            if(x==1){ans[i]=p[w[y]];continue;}
            if(x%2==0) ans[i]=answer(root[w[y]],1,n,y);
        }
        else
        {
            q[i].id=w[y];
            insert(root[w[y]],1,n,y,-1);
            w[y]=x;
            insert(root[w[y]],1,n,y,1);
        }
    }
    int r=0,t=0;
    for(int i=1;i<=n;i++) w[i]=swp[i];
    for(int i=1;i<=qtot;i++)
    {
        while(r<qt[i].y){++r;change(n,0,w[r]);}
        while(r>qt[i].y){change(n,w[r],0);--r;}
        for(;t<qt[i].t;)
        {
            t++;
            if(q[t].opt!=1) continue;
            if(q[t].y<=qt[i].y) change(n,w[q[t].y],q[t].x);
            w[q[t].y]=q[t].x;
        }
        for(;t>qt[i].t;t--)
        {
            if(q[t].opt!=1) continue;
            if(q[t].y<=qt[i].y) change(n,w[q[t].y],q[t].id);
            w[q[t].y]=q[t].id;
        }
        ans[qt[i].t]=t_answer(n,tot[w[qt[i].y]]);
    }
    for(int i=1;i<=k;i++)
    if(q[i].opt==2)printf("%d\n",ans[i]);
    return 0;
}
```
