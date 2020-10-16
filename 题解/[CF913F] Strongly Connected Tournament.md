### [链接](http://codeforces.com/problemset/problem/913/F)
考虑dp。用 $f_i$ 表示 $i$ 个点的答案，枚举缩点后入度为0的联通块的大小 $j$ 转移：

$$f_i=\sum_{j=1}^{i}g_jh_{i,j}\times(f_j+\frac{j(j-1)}{2}+j(i-j)+f_{i-j})$$

$g_j$ 表示 $j$ 成为一个联通块的概率，$h_{i,j}$ 表示 $i$ 个点中前 $j$ 个点可以缩点，且缩点后入度为0。

右边括号内分别对应前 $j$ 完成的期望，当前用于前 $j$ 的代价，当前用于区分 $j$ 和 $i-j$ 的代价，后 $i-j$ 完成的期望。

注意这里不需要考虑这一轮后 $i-j$ 的代价。其实可以单纯认为这一轮没有比较后 $i-j$，因此后 $i-j$ 的期望就是 $f_{i-j}$。

然后就是推 $h_{i,j}$。可以枚举新加入一个点的贡献，即枚举它在不在缩点后入度为0的联通块中。

$$h_{i,j}=p^{i-j}h_{i-1,j-1}+(1-p)^{j}h_{i-1,j}$$

然后处理 $g_j$。这个显然可以用总概率减去不合法概率，即

$$g_i=1-\sum_{j=1}^{n}g_jh_{i,j}$$

递推即可。复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 998244353
#define ll long long
#define N 2010
using namespace std;
int ksm(int a,int b=mod-2)
{
	int r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=1ll*r*a%mod;
		a=1ll*a*a%mod;
	}
	return r;
}
int pw[N],ipw[N];
int f[N],g[N][N],s[N];
int main()
{
	int n,p,b;
	scanf("%d%d%d",&n,&p,&b);p=1ll*p*ksm(b)%mod;
	pw[0]=ipw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=1ll*pw[i-1]*p%mod,ipw[i]=1ll*ipw[i-1]*(1-p+mod)%mod;
	g[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		g[i][0]=1;
		for(int j=1;j<=n;j++)
		g[i][j]=(1ll*pw[i-j]*g[i-1][j-1]%mod+1ll*ipw[j]*g[i-1][j]%mod)%mod;
	}
	for(int i=1;i<=n;i++)
	{
		s[i]=1;
		for(int j=1;j<=i-1;j++)
		s[i]=(s[i]-1ll*s[j]*g[i][j]%mod+mod)%mod;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		f[i]=(f[i]+1ll*s[j]*g[i][j]%mod*(1ll*f[j]+f[i-j]+1ll*j*(i-j)%mod+1ll*j*(j-1)/2%mod)%mod)%mod;
		f[i]=1ll*(f[i]+1ll*s[i]*(1ll*i*(i-1)/2%mod)%mod)*ksm((1-s[i]+mod)%mod)%mod;
	}
	printf("%d",f[n]);
	return 0;
}
```
