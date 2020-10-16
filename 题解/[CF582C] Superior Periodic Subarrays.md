### [链接](https://codeforces.com/problemset/problem/582/C)
考虑如何判定一个子串是否满足条件：

首先我们先找出他们之间的 $g=\gcd$。显然，对于 $a_i\equiv a_{l+j}\pmod g$ 我们要求 $a_{l+j}\geq a_i$。

也就是说，我们把 $\gcd$ 相同的看做一组，那么相同组中只有最大值能在子串中出现。

那么按照套路，我们枚举 $\gcd$。由于一个数字的因子不超过 $O(\sqrt n)$，所以这样完全可行。

然后考虑将相同的看做一组，求组内的最大值。这样可能会出现多个最大值，那么显然这些都可以记录答案。

考虑如何统计。可以发现如果我们把可以记录答案的部分标1，不能的标0，那么我们可以处理一个前缀和。这里需要注意如果有0应当直接清0而不是继承上一位的结果。

这样，我们就处理出到 $i$ 结束可以处理的最大长度。然后我们再记录一个数组 $g$ 表示长度为最大 $i$ 的固定右端点的序列贡献是多少。显然对于 $[i=g]$ 做一次前缀和即可。

复杂度 $O(n\sqrt n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 400010
#define ll long long
using namespace std;
int a[N],f[N],g[N],h[N],c[N];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) g[i]=gcd(i,n);
	ll ans=0;
	for(int d=1;d<n;d++)
	if(n%d==0)
	{
		for(int i=1;i<=n;i++) c[i]=c[i-1]+(g[i]==d);
		for(int i=0;i<d;i++) f[i]=0;
		for(int i=0;i<n;i++) f[i%d]=max(f[i%d],a[i]);
		for(int i=0;i<n;i++) h[i]=h[i+n]=f[i%d]==a[i];
		for(int i=n*2-2;i>=0;i--)
			if(h[i]) h[i]+=h[i+1];
		for(int i=0;i<n;i++) ans+=c[min(n-1,h[i])];
	}
	printf("%lld\n",ans);
	return 0;
}
```
