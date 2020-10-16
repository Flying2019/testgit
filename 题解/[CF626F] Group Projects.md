### [链接](https://codeforces.com/problemset/problem/626/F)
按照套路，看到只和子集有关先排序。

可以发现，这样题目就转换成：数轴上有 $n$ 个点，你可以分成若干组，定义长度为每组的左端点和右端点。每组的长度和不大于 $k$。最后求所有可行方案的总数。

可以发现，这样对于某个点来说，组中的左端点位置不再重要，只需要知道有多少组的左端点和右端点经过它即可。

这样就可以dp了。用 $f_{i,j,k}$ 表示前 $i$ 个点，$j$ 个组还没有右端点，总长为 $k$ 的方案数。

可以发现，对于某个点 $i$，可以进行：

1. 不做任何操作。这样的代价是 $j\times (a_i-a_{i-1})$，方案数 $\times (j+1)$。
2. 成为一个左端点。这样的代价是 $j\times (a_i-a_{i-1})$，方案数 $\times 1$。
2. 成为一个右端点。这样的代价是 $j\times (a_i-a_{i-1})$，方案数 $\times (j+1)$。

分别转移即可。复杂度 $O(n^2m)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 1010
#define ll long long
#define mod 1000000007
using namespace std;
int v[N];
int f[N][N][M];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	sort(v+1,v+n+1);
	for(int i=0;i<n;i++) v[i]=v[i+1]-v[i];
	f[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=m-v[i]*j;k++)
			{
				f[i+1][j][k+v[i]*j]=(f[i+1][j][k+v[i]*j]+1ll*f[i][j][k]*(j+1)%mod)%mod;
				f[i+1][j+1][k+v[i]*j]=(f[i+1][j+1][k+v[i]*j]+f[i][j][k])%mod;
				if(j) f[i+1][j-1][k+v[i]*j]=(f[i+1][j-1][k+v[i]*j]+1ll*f[i][j][k]*j%mod)%mod;
			}
	int ans=0;
	for(int i=0;i<=m;i++) ans=(ans+f[n][0][i])%mod;
	printf("%d\n",ans);
	return 0;
}
```
