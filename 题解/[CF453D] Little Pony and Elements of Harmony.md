### [链接](https://codeforces.com/contest/453/problem/D)
首先，这个$count(i\ \text{xor}\ j)$不是很好处理，但是考虑$b[i]$和$count(i\ \text{xor}\ j)$都是定值，所以可以把$b[count(i\ \text{xor}\ j)]$整体看成函数$g[i\ \text{xor}\ j]$。

那么式子就变成$f_t(i)=\sum_{j}f_{t-1}(j)*g[i\ \text{xor}\ j]$，整理一下可得$f_t(i\ \text{xor}\ j)=f_{t-1}(i)*g[j]$，是一个fwt卷积形式，所以直接快速幂即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
#define N 21
#define ll long long
ll mod;
ll f[1<<N],a[N+2],g[1<<N];
int n;
ll mul(ll x,ll y){return ((x*y-(ll)((long double)x*y/mod+0.5)*mod)%mod+mod)%mod;}
ll ksm(ll a,ll b,ll res=1)
{
	for(;b;b>>=1)
	{
		if(b&1) res=mul(res,a);
		a=mul(a,a);
	}
	return res;
}
void fwt(ll f[],int n)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;k++)
			{
				ll a=f[j+k],b=f[i+j+k];
				f[j+k]=(a+b)%mod;
				f[i+j+k]=(a-b+mod)%mod;
			}
}
int main()
{
	ll k;
	scanf("%d%lld%lld",&n,&k,&mod);
	mod<<=n;
	for(int i=0;i<(1<<n);i++) scanf("%d",&f[i]);
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	n=1<<n;
	for(int i=0;i<n;i++) g[i]=a[__builtin_popcount(i)];
	fwt(f,n);
	fwt(g,n);
	for(int i=0;i<n;i++) f[i]=ksm(g[i],k,f[i]);
	fwt(f,n);
	for(int i=0;i<n;i++) printf("%lld\n",f[i]/n);
	return 0;
}
```
