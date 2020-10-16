### [链接](http://codeforces.com/contest/461/problem/E)
首先考虑Appleman的策略：一定尽可能多地匹配。考虑假如匹配 $s1+s2+s3$ 其中 $s1+s2,s2+s3$ 都是子串，那么优先匹配 $s1+s2$ 一定不会比匹配 $ s2+s3$ 劣。

显然可以二分答案。

设 $f[i][j][k]$ 表示填 $i$ 次，第 $i$ 次填进去的子串开头的字母是 $j$，第 $i+1$ 次填进去的子串开头的字母是 $k$ 能填出的最小长度。

显然 $f[1][i][j]$ 其实就是最小的以 $i$ 开头，$j$ 结尾且不是 $t$ 的子串的最短字符串的长度。

这个可以直接预处理 $t$ 所有长度为 $l$ 的不同字串个数。

然后可以列出方程 $f[p+1][i][j]=min(f[p][i][k]+f[1][k][j]) $

这很显然可以用矩阵快速幂解决。

时间复杂度 $O(m\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define C 4
#define P 16
#define ll long long
using namespace std;
struct matrix{
	ll num[C][C];
	ll* operator [](int a){return num[a];}
	matrix(ll a=0){memset(num,0,sizeof(num));for(int _=0;_<C;_++) for(int __=0;__<C;__++) num[_][__]=a;}
};
int ch[N*P][C],m,cnt,maxd;
ll n;
matrix operator *(matrix a,matrix b)
{
	matrix c(n+1);
	for(int k=0;k<C;k++)
		for(int i=0;i<C;i++)
			for(int j=0;j<C;j++)
			c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
	return c;
}
char str[N];
bool vis[N*P];
int f[C][C][P];
void insert(int p)
{
	int u=0;
	for(int i=p;i<=min(m-1,p+maxd-1);i++)
	{
		int v=str[i]-'A';
		if(!ch[u][v]) ch[u][v]=++cnt;
		u=ch[u][v];
		if(!vis[u]) vis[u]=true,f[str[p]-'A'][v][i-p+1]++;
	}
}
ll ksm(ll a,ll b)
{
	ll r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=r*a;
		a=a*a; 
	}
	return r;
}
matrix ksm(matrix a,ll b)
{
	matrix r=a;
	--b;
	for(;b;b>>=1)
	{
		if(b&1) r=r*a;
		a=a*a; 
	}
	return r;
}
matrix g;
bool check(ll x)
{
	matrix u=ksm(g,x);
	for(int i=0;i<C;i++)
		for(int j=0;j<C;j++)
		if(u[i][j]<n) return true;
	return false;
}
int main()
{
	scanf("%lld%s",&n,str);
	m=strlen(str);
	maxd=min(11,m+1);
	for(int i=0;i<m-1;i++) insert(i);
	for(int i=0;i<C;i++)
		for(int j=0;j<C;j++)
			for(int k=maxd;k>=2;k--)
			if(f[i][j][k]!=ksm(C,k-2)) g[i][j]=k-1;
	ll l=1,r=n;
	while(l<r)
	{
		ll mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	printf("%lld\n",l);
	return 0;
}
```
