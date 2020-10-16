### [链接](http://codeforces.com/problemset/problem/538/F)
很小清新的一道题。

首先可以发现，一个点对应的父亲数量其实不多。具体来说，点 $u$ 在 $k$ 叉树中对应的点是 $\lfloor\frac {n-2} k\rfloor+1$。

那么我们枚举它的可行父亲，可以发现对应的 $k$ 是一段区间。

具体来说直接数论分块，然后差分处理即可。

复杂度 $O(n\sqrt n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int v[N];
int ans[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=2;i<=n;i++)
	{
		int l=1,r=0;
		const int m=i-2;
		for(;l<=m;l=r+1)
		{
			r=m/(m/l);
			if(v[m/l+1]>v[i]) ans[l]++,ans[r+1]--;
		}
		if(v[1]>v[i]) ans[l]++;
	}
	for(int i=1;i<n;i++) ans[i]+=ans[i-1],printf("%d ",ans[i]);
	return 0;
}
```
