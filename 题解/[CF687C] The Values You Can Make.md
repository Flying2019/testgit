### [链接](https://codeforces.com/problemset/problem/687/C)
考虑dp。可以发现在这道题中每枚硬币有三种状态：不被选中，被选中但不在集合中，被选中且在集合中。

可以发现 $n,m$ 非常的小，可以直接dp，用 $f_{i,j,k}$ 表示到第 $i$ 枚硬币，被选中的硬币总价值为 $j$，集合中硬币总价值为 $k$ 是否可行。

空间可能会炸，需要滚动数组。

很显然这个dp方程是 $O(n^3)$ 的，用bitset优化可以达到 $O(\frac{n^3}{\omega})$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<bitset>
#define N 1010
#define M 510
using namespace std;
bitset<N> f[2][M],o;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	f[0][0][0]=true;
	for(int i=0;i<=k;i++) o[i]=1;
	for(int i=1;i<=n;i++)
	{
		int c;
		int u=i&1,p=!u;
		scanf("%d",&c);
		for(int j=0;j<=k;j++) f[u][j]=f[p][j];
		for(int j=0;j<=k-c;j++)
		f[u][j+c]|=(f[p][j]|(f[p][j]<<c))&o;
	}
	int cnt=0;
	for(int i=0;i<=k;i++)
	if(f[n&1][k][i]) cnt++;
	printf("%d\n",cnt);
	for(int i=0;i<=k;i++)
	if(f[n&1][k][i]) printf("%d ",i);
	return 0;
}

```

