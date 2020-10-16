### [链接](https://codeforces.com/contest/388/problem/D)
考虑数位dp。

用 $f_{i,j,k}$ 表示从第 $j$ 位到最高位已经选了 $j$ 个基，通过 $+2^i$ 是否超过 $n$。

可以发现通过分类讨论可以处理出对应情况。具体来说，我们判断当前 $i$ 是否填一个新的基，如果是那么这一位只有一种选择 $2^i$。否则这一位可以根据前几位的推出，方案数 $2^j$。

那么对于可能超过的情况，首先对于 $n$ 这一位分类讨论。如果 $n$ 这一位为0，那么这一位就不能填东西了。如果为1那么特判掉超过情况，同上进行转移。

复杂度 $O(\log^2 n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define N 30
using namespace std;
int f[N+2][N+2][2];
int main()
{
	int n;
	scanf("%d",&n);
	f[N][0][1]=1;
	for(int i=N;i;i--)
		for(int j=0;j<=N;j++)
		{
			f[i-1][j][0]=(f[i-1][j][0]+f[i][j][0]*(1ll<<j))%mod;
			f[i-1][j+1][0]=(f[i-1][j+1][0]+f[i][j][0])%mod;
			if((n>>(i-1))&1)
			{
				f[i-1][j][0]=(f[i-1][j][0]+(j?1ll<<(j-1):1ll)*f[i][j][1])%mod;
				f[i-1][j][1]=(f[i-1][j][1]+(j?1ll<<(j-1):0)*f[i][j][1])%mod;
				f[i-1][j+1][1]=(f[i-1][j+1][1]+f[i][j][1])%mod;
			}
			else f[i-1][j][1]=(f[i-1][j][1]+(j?1ll<<(j-1):1ll)*f[i][j][1])%mod;
		}
	int ans=0;
	for(int i=0;i<=N;i++) ans=(1ll*ans+f[0][i][0]+f[0][i][1])%mod;
	printf("%d",ans);
	return 0;
}
```
