### [链接](https://codeforces.com/contest/650/problem/D)
一般遇到修改单点且立刻撤销的题，普遍套路就是求前缀后缀然后合并。

这里也是一样。首先明显可以发现，假如原序列的最长上升子序列是 $r$，那么修改后一定是 $[r-1,r+1]$ 中的。

首先如何判断经过某个点的最长上升子序列。这个我们记录一下对于某个值来说的前缀和后缀的答案，最后最后加起来-1即可。

我们不妨分类讨论。首先是 +1 的情况。这个比较好处理，因为这样方案中一定会 $x$，即直接询问离线，按 $x$ 排序，然后查到 $x$ 时记录答案，最后处理即可。

然后是 -1 的情况。这个稍微麻烦一点，即最后 $x$ 是原上升子序列的必经之路，而修改后经过 $x$ 的最长上升子序列小于 $r$。对于后者和上面一样方法处理，而对于前者，我们可以预处理出一个数组，用来处理某个长度 $l$ 的关键点个数，这里关键点是指可以成为某个上升子序列，且当前长度为 $l$。显然如果某个点在必经之路上，那么它对应长度的关键点数量为1。

最后 0 就是剩下的情况。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 800010
using namespace std;
int a[N],pa[N],n,m;
int tn,pr[N],sf[N];
struct tree_arr{
	int v[N],opt;
	void add(int x,int y){if(opt) x=tn-x;for(;x<=tn;x+=(x&-x)) v[x]=max(v[x],y); }
	int qry(int x){if(opt) x=tn-x;int r=0; for(;x;x-=(x&-x)) r=max(r,v[x]); return r;}
	void clr(){for(int i=1;i<=tn;i++) v[i]=0;}
}t[2];
struct node{
	int x,y,id,pr,sf;
	bool operator <(const node a)const{return x==a.x?y<a.y:x<a.x;}
}q[N];
int cnt[N],ans[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),pa[++tn]=a[i];
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].x,&q[i].y),q[i].id=i,pa[++tn]=q[i].y;
	sort(pa+1,pa+tn+1);
	tn=unique(pa+1,pa+tn+1)-pa-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(pa+1,pa+tn+1,a[i])-pa;
	for(int i=1;i<=m;i++) q[i].y=lower_bound(pa+1,pa+tn+1,q[i].y)-pa;
	sort(q+1,q+m+1);
	++tn,t[1].opt=1;
    for(int i=1;i<=n;i++) t[0].add(a[i],pr[i]=t[0].qry(a[i]-1)+1);
    for(int i=n;i>=1;i--) t[1].add(a[i],sf[i]=t[1].qry(a[i]+1)+1);
    int res=0;
    for(int i=1;i<=n;i++) res=max(res,pr[i]+sf[i]-1);
    for(int i=1;i<=n;i++) if(pr[i]+sf[i]-1==res) ++cnt[pr[i]];
    t[0].clr(),t[1].clr();
    int u=1;
    for(int i=1;i<=m;i++)
    {
        for(;u<q[i].x;u++) t[0].add(a[u],pr[u]);
        q[i].pr=t[0].qry(q[i].y-1);
    }
    u=n;
    for(int i=m;i>=1;i--)
    {
        for(;u>q[i].x;u--) t[1].add(a[u],sf[u]);
        q[i].sf=t[1].qry(q[i].y+1);
    }
    for(int i=1;i<=m;i++)
    {
        if(q[i].sf+q[i].pr+1>res) ans[q[i].id]=q[i].sf+q[i].pr+1;
        else if(pr[q[i].x]+sf[q[i].x]-1==res && cnt[pr[q[i].x]]==1 && q[i].sf+q[i].pr+1<res) ans[q[i].id]=res-1;
        else ans[q[i].id]=res;
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```
