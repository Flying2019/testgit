### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102647/problem/D)
### 题目大意
$n×n$ 棋盘上的 $(n+1)^2$ 个点，求从 $(0,0)$ 出发的直线，恰好通过 $m$ 个点的方案数。

定义两个方案是不同的，当且仅当存在一个点属于方案A不属于方案B。
### 题解
首先我们不妨假设我们在 $y=x$ 这条直线的下方走，可以发现最后将答案 $\times 2$ 即可（对于走 $y=x$ 直接特判）。

可以发现，假如我们向 $\tan\alpha=\frac{b}{a}\ (\gcd(a,b)=1\ , \ a>b)$ 的方向走，那么经过的点次数就是 $\lfloor\frac{n}{a}\rfloor+1$。

所以我们可以得到式子 $ans=\sum_{i=2}^{n}{\sum_{j=1}^{i-1}[\ \gcd(i,j)=1\ ][\ \lfloor\frac{n}{i}\rfloor}+1=m\ ]$。可以发现被求和的式子本质就是将 $[\ \lfloor\frac{n}{i}\rfloor+1=m\ ]$ 求了 $φ(i)$ 遍。

所以 $ans=\sum_{i=2}^{n}φ(i)[\ \lfloor\frac{n}{i}\rfloor+1=m\ ]$。

可以发现，符合后面那个式子的 $i$ 是一段区间，本质就是一段 $φ(i)$ 的和，线性筛出 $φ(i)$ 并前缀和即可。复杂度 $O(n+T)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define N 5000010
#define ll long long
int phi[N],pr[N],tot;
bool p[N];
ll sum[N];
void init(int n)
{
	for(register int i=2;i<=n;i++)
	{
		if(!p[i])
		{
			pr[++tot]=i;
			phi[i]=i-1;
		}
		for(register int j=1;j<=tot && 1ll*i*pr[j]<=n;j++)
		{
			int k=i*pr[j];
			p[k]=1;
			if(i%pr[j]) phi[k]=phi[i]*(pr[j]-1);
			else{phi[k]=phi[i]*pr[j]; break;}
		}
	}
}

int main()
{
	init(N-10);
	for(register int i=1;i<=N-10;i++) sum[i]=phi[i]+sum[i-1];
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		++n;
		if(m==n){puts("3");continue;}
		if(m==1){puts("1");continue;}
		int l=(n-1)/m,r=(n-1)/(m-1);
		printf("%lld\n",(sum[r]-sum[l])*2);
	}
	return 0;
}
```
