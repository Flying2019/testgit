### [链接](https://www.luogu.com.cn/problem/CF891E)
神仙生成函数题。。。

每一步的贡献和就是最后的贡献，所以显然有
$$ans=\prod_{i=1}^{n}a_i\ -\sum_{\sum{b_i}=k}\frac{k!}{\prod{b_i}}\prod_{i-1}^{n}(a_i-b_i)\times n^{-k}$$

很显然只需要求出后面那个式子即可。
$$\sum_{\sum{b_i}=k}\frac{k!}{\prod{b_i}}\prod_{i-1}^{n}(a_i-b_i)\times n^{-k}$$
化简可得
$$=\frac{k!}{n^k}\sum_{\sum{b_i}=k}\prod_{i-1}^{n}\frac{a_i-b_i}{b_i!}$$
考虑令生成函数
$$F_i(x)=\sum_{j=0}^{\infty}{\frac{(a_i-j)x^j}{j!}}$$
可以发现
$$\text{原式}=\frac{k!}{n^k}[x^k]\prod_{i=1}^{n}\sum_{j=0}^{\infty}\frac{(a_i-j)x^j}{j!}$$
由 $e^x=\sum_{i=0}{\frac{x^i}{i!}}$ 可得
$$\text{原式}=\frac{k!}{n^k}[x^k](e^{nx}\prod_{i=1}^{n}(a_i-x))$$
显然 $\prod_{i=1}^{n}(a_i-x)$ 可以直接暴力求出。假设其结果为 $\sum_{i=0}^{n}{c_i x^i}$。

可以推出
$$\text{原式}=\frac{k!}{n^k}[x^k]\sum_{i=0}^{\infty}\frac{{(nx)^i}}{i!}\sum_{j=0}^{n}{c_j x^j}$$

令 $t=i+j$。由于只取 $x^k$ 的系数，所以 $t=k$。可得：

$$\text{原式}=\sum_{i=0}^{k}\frac{k^{\underline{i}}c_i}{i!}$$
所以最后可得
$$ans=\prod{a_i}-\sum_{i=0}^{min(n,k)}\frac{k^{\underline{i}}c_i}{i!}$$
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define mod 1000000007
using namespace std;
int f[N],a[N],c[N],fac[N],inv[N],res[N];
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
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	c[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++) res[j]=1ll*c[j]*a[i]%mod;
		for(int j=n;j;j--) c[j]=(res[j]-c[j-1]+mod)%mod;
		c[0]=res[0];
	}
	int ans=1;
	for(int i=1;i<=n;i++) ans=1ll*ans*a[i]%mod;
	for(int i=0;i<=min(n,k);i++)
	{
		int r=1;
		for(int j=k;j>=k-i+1;j--) r=1ll*r*j%mod;
		ans=(ans-1ll*r*c[i]%mod*ksm(ksm(n,i))%mod+mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```
