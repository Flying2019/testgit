### [链接](https://codeforces.com/contest/632/problem/E)
很明显一种做法是用多项式快速幂搞，但是由于常数太大导致时限开了5s。

这就让暴力有可乘之机了。

当然 $O(n^4)$ 的暴力显然是跑不过去的。考虑转换题意，我们不妨假设小偷拿的全都是最小价值的物品，然后我们把所有物品价值减去这个东西。

那么题目就变成了：最多拿 $k$ 个商品，问可能的价值。

再转换题意，即对于所有价值，求它最少要几个商品才能组合。

这个就是很明显的背包了。直接dp即可。

复杂度 $O(n^3)$，跑得飞快。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
#define M 1010
using namespace std;
int a[M],d[M],f[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) d[i]=a[i]-a[1];
	memset(f,60,sizeof(f));
	f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=d[i];j<=N-10;j++) f[j]=min(f[j],f[j-d[i]]+1);
    for(int i=0;i<=N-10;i++)
        if(f[i]<=m) printf("%d ",m*a[1]+i);
	return 0;
}
```
