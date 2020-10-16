### [链接](https://atcoder.jp/contests/joisc2014/tasks/joisc2014_c)[_](https://www.luogu.com.cn/problem/AT1219)
这题很像区间众数，而区间众数是没有log做法的，所以先往根号方面想。

考虑询问离线，但是直接莫队我们很难处理删除一个数的操作。考虑一种特殊的莫队：回滚莫队。

考虑按莫队的方式排序后，相邻两个询问的左端点如果在一个块中，左端点的差不大于块长，那么由于右端点单调递增，我们可以很方便地从该块的最右端只通过加入数字来得到答案。

换句话说，一开始初始化左右端点是位于该块最右端的空区间。然后对于每次询问，先将右端点增值询问区间右端点，然后记录下当前值。

对于移动左端点的过程，记录所有修改信息。移动完成之后撤销移动左端点时的修改信息，同时左端点归位到最右端，注意右端点不必进行撤销。

特别的，当区间左右端点在同一块内，我们直接暴力处理即可。

当两个区间左端点不在同一块内时，我们暴力清空数组，重新计算。由于块最多 $O(\sqrt{n})$ 个，所以时间复杂度是对的。

总时间复杂度 $O((n+m)\sqrt{n})$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
ll a[N],p[N],ans[N];
int cnt[N];
ll maxn,pmaxn;
int qt[N],pt;
void save(){pmaxn=maxn;pt=0;}
void add(int x){qt[++pt]=a[x];cnt[a[x]]++,maxn=max(maxn,p[a[x]]*cnt[a[x]]);}
void back(){while(pt) --cnt[qt[pt--]];maxn=pmaxn;}
int bl[N];
struct ques{
	int l,r,id;
	bool operator <(const ques a)const{return bl[l]==bl[a.l]?r<a.r:bl[l]<bl[a.l];}
}q[N];
int sq[N];
int main()
{
	int n,m;
	int B=233;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[i]=a[i],bl[i]=i/B;
	sort(p+1,p+n+1);
	int tn=unique(p+1,p+n+1)-p-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(p+1,p+tn+1,a[i])-p;
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int l=0,r=0;
	for(int i=1;i<=m;i++)
	{
		if(i==1 || bl[q[i].l]!=bl[q[i-1].l]){for(int j=1;j<=n;j++) cnt[j]=0;maxn=pmaxn=0;l=min(bl[q[i].l]*B+B,n);r=l-1;}
		if(bl[q[i].l]==bl[q[i].r])
		{
			ll res=0;
			for(int j=q[i].l;j<=q[i].r;j++)
			sq[a[j]]++,res=max(res,1ll*p[a[j]]*sq[a[j]]);
			ans[q[i].id]=res;
			for(int j=q[i].l;j<=q[i].r;j++)
			sq[a[j]]--;
			continue;
		}
		while(r<q[i].r) add(++r);
		save();while(l>q[i].l) add(--l);
		ans[q[i].id]=maxn;
		back();
		l=min(bl[q[i].l]*B+B,n);
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
/*
10 10
1 2 1 1 2 2 1 1 1 2
1 5
2 4
2 7
4 8
3 6
2 9
4 10
2 7
1 10
7 10
*/
```
