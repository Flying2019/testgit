### [链接](https://codeforces.com/contest/364/problem/D)
### 题目大意
给定一个长度为 $n$ 的序列，问从中选出 $\frac n 2$ 的数字，最大的 $\text{gcd}$ 是多少。
### 题解
首先考虑一种贪心：我们钦定一个数字 $x$，假设它在最后所选的集合中。

然后我们找出它的所有因数 $p_i$，排一个序。然后记录一个数组 $c_j$，对于所有数字 $a_i$，我们二分出 $\operatorname{gcd}(a_i,x)$ 的位置 $p$，令 $c_p$ 加1。

然后我们做一遍因数前缀和，即 $c_i\leftarrow\sum_{j=i+1}^{t}[p_i|p_j]c_j+c_i$。

很明显对于这样做完后第一个 $c_i\geq \frac n 2$ 的 $p_i$ 就是答案。

但是这样的前提是 $x$ 在最后所选的集合中。但是这个概率只有 $\frac 1 2$。所以多枚举几次就好了。

复杂度 $O(Tn\log n+T\sqrt a)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
ll a[N];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll pr[N],t;
int cnt[N];
int main()
{
	int n;
	scanf("%d",&n);
	srand(n*2);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ll ans=0;
	for(int _=0;_<=10;_++)
	{
		memset(cnt,0,sizeof(cnt));
		ll x=a[1ll*rand()*rand()%n+1];
		t=0;
		for(int i=1;1ll*i*i<=x;i++)
		if(x%i==0){pr[++t]=i;if(1ll*i*i!=x) pr[++t]=x/i;}
		sort(pr+1,pr+t+1);
		for(int i=1;i<=n;i++)
			cnt[lower_bound(pr+1,pr+t+1,gcd(x,a[i]))-pr]++;
		for(int i=1;i<=t;i++)
			for(int j=i+1;j<=t;j++)
			if(pr[j]%pr[i]==0) cnt[i]+=cnt[j];
		for(int i=t;i;i--)
		if(2*cnt[i]>=n) ans=max(ans,pr[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```
