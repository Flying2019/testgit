### [链接](https://codeforces.com/contest/631/problem/E)
斜率优化dp。

首先可以发现，令 $s_i=\sum_{j=1}^{j}a_j$，将 $i$ 移到 $j$ 的影响 $=s_i-s_j+a_i*(j-i)$。

所以可以先处理出所有的结果，然后处理出最大化的影响。

显然有一个 $O(n^2)$ 的dp。但是这里可以发现，$x,y$ 两项差为 $\frac {s_x-s_y}{x-y}$，显然可以斜率优化。直接处理即可。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
ll f[N],a[N];
ll s[N];
int q[N],qt;
int solve(ll v)
{
	int l=2,r=qt,res=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(s[q[mid]]-s[q[mid-1]]<=v*(q[mid]-q[mid-1])) l=mid+1,res=mid;
		else r=mid-1;
	}
	return q[res];
}
int main()
{
	int n;
	ll sm=0,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i],sm+=1ll*a[i]*i;
	q[qt=1]=0;
	for(int i=1;i<=n;i++)
	{
		for(;qt>1 && (s[q[qt]]-s[q[qt-1]])*(i-q[qt])>=(s[i]-s[q[qt]])*(q[qt]-q[qt-1]);--qt);
		q[++qt]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int p=solve(a[i]);
		ans=max(ans,(p-i)*a[i]+s[i]-s[p]);
	}
	printf("%lld\n",sm+ans);
	return 0;
}
```
