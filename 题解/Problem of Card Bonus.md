### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102657/problem/E)
### 题目大意
有 $n$ 个物品，每种物品有三种数值 $a_i,b_i,c_i$。所有数字均为非负整数，保证 $a_i\leq b_i(1\leq i \leq n)$。

给定一个数 $P$，求选出一个物品集合 $S$，求满足 $\sum_{i\in S}a_i\leq P\leq \sum_{i\in S}b_i$ 时 $\sum_{i\in S}c_i$ 的最小值。
### 题解
考虑dp。用 $f_{i,j}$ 表示前 $i$ 个数中满足 $\sum_{i\in S}a_i\leq j\leq \sum_{i\in S}b_i$ 时 $\sum_{i\in S}c_i$ 的最小值。

显然可知转移
$$f_{i,j}=\min(f_{i-1,j},\ \min_{k\in[\ j-b_i\ ,\ j-a_i\ ]}(f_{i-1,k}+c_i))$$
可以发现，对于满足 $k\in[\ j-b_i\ ,\ j-a_i\ ]$ 的点在转移后一定满足 $f_{i,j}$ 的定义。直接转移是正确的。

考虑由于对于每个 $i$，区间 $[\ j-b_i\ ,\ j-a_i\ ]$ 的长度时确定的，直接单调队列即可。复杂度 $O(nP)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 10010
#define ll long long
using namespace std;
int a[N],b[N],c[N];
int n,P;
ll q[N*2];
int pos[N*2],ql,qr;
ll f[2][N];
int main()
{
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		scanf("%d%d",&n,&P);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		for(int i=1;i<=n;i++) scanf("%d",&c[i]);
		memset(f,60,sizeof(f));
		f[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			int u=i&1,p=!u;
			ql=qr=0;
			memset(f[u],60,sizeof(f[u]));
			for(int j=0;j<=P;j++)
			{
				if(j<a[i]){f[u][j]=f[p][j];continue;}
				while(qr>ql && q[qr]>=f[p][j-a[i]]) --qr;
				q[++qr]=f[p][j-a[i]]; pos[qr]=j-a[i];
				if(pos[ql+1]<j-b[i]) ++ql;
				f[u][j]=min(f[p][j],q[ql+1]+c[i]);
			}
		}
		printf("%lld\n",f[n&1][P]>=1e15?-1:f[n&1][P]);
	}
	
	return 0;
}
```
