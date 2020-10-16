### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102647/problem/A)
### 题目大意
给定一个长度为 $m(n\leq 4\times 10^6)$ 的序列 $a_i\leq 20000$，询问 $m(m\leq 2\times 10^5)$ 次，每次一个数 $b_i\leq 20000$，求序列中有多少个区间满足区间 $\gcd$ 结果为 $b_i$。
### 题解
首先可以发现一个性质：一个数字的因数个数是 $O(\log n)$ 级别的。

考虑一个暴力的做法：每次插入一个数后处理所有其因数的出现个数，即对前一个数所有可能出现的 $\gcd$ 进行处理，统计每种 $\gcd$ 的出现次数。

根据上面那个性质，前一个数所有可能出现的 $\gcd$ 也是 $O(\log n)$ 级别，可以意外发现这样的处理次数是 $O(\log n)$ 的。

随便套上一个map即可通过。复杂度 $O(n\log^2 a)$，但是界很宽（因为大部分数字的因数个数其实只有个位数）。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#define N 4000010
#define ll long long
#define mi map<int,ll>
using namespace std;
int a[N];
mi ans,u,pre;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		u.swap(pre);
		u.clear();
		scanf("%d",&a[i]);
		u[a[i]]++;
		for(auto t:pre) u[__gcd(a[i],t.first)]+=t.second;
		for(auto t:u) ans[t.first]+=t.second;
	}
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int x;
		scanf("%d", &x);
		printf("%lld\n", ans[x]);
	}
	return 0;
}
```
