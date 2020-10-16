### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102658/problem/A)
### 题目大意
有 $n$ 堆石子，每堆 $a_i$ 颗。A和B玩取石子游戏，其中A先手，但是B可以在游戏开始前将每堆石子拿走 $x$ 颗，并且要求没有任何一堆石子被拿光，求方案数。
### 题解
考虑SG函数。也就是最后要求 $\sum_{x=0}^{x<\min(a_i)}[\ \bigoplus_i(a_i-x) =0\ ]$。

考虑数位dp。可以发现如果没有退位，那么要求 $n$ 个数的这一位要么有偶数个1（$x$ 的当前位为0），要么有偶数个0（$x$ 的当前位为1）。

接下来考虑退位。考虑如果 $x$ 在 $i$ 这一位取1，那么退位的一定是按后 $i $ 位从小到大排序后的一段前缀。

考虑用 $f_{i,j}$ 表示第 $i$ 位，上一位退位为长度前 $j$ 的区间。可以发现退位对当前位来说相当于异或操作。所以分别考虑以下即可。

对于排序可以直接用基数排序。总复杂度 $O(n\log a)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#define N 200010
#define M 63
#define ll long long
using namespace std;
ll f[2][N],cnt[M+10];
ll num[N];
vector<ll>v[2];
int main()
{
	int n;
	scanf("%d",&n);
	ll minn=1e18;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&num[i]);
		minn=min(minn,num[i]);
		for(int j=0;j<M;j++)
		if((num[i]>>j)&1)cnt[j]++;
	}
	f[0][0]=1;
	int u=0;
	for(int i=0;i<M;i++)
	{
		u=!u;
		int p=!u;
		memset(f[u],0,sizeof(f[u]));
		int c0=n-cnt[i],c=0;
		for(int j=0;j<=n;j++)
		{
			if(j)
			{
				if((num[j]>>i)&1) ++c0;
				else --c0,++c;
			}
			if(c0%2==0) f[u][c+c0]+=f[p][j];
			if((n-c0)%2==0) f[u][c]+=f[p][j];
		}
		v[0].clear();v[1].clear();
		int tot=0;
		for(int j=1;j<=n;j++) v[(num[j]>>i)&1].push_back(num[j]);
		for(int _=0;_<=1;_++)
			for(ll u:v[_]) num[++tot]=u;
	}
	ll res=0;
	for(int j=1;j<=n;j++) res^=num[j]-minn;
	printf("%lld\n",f[u][0]-(res==0));
	return 0;
}
```
