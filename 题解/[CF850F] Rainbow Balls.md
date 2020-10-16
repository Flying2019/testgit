### [链接](https://codeforces.com/contest/850/problem/F)
考虑枚举最后留下的球的颜色，要求的是最后留下该球的期望步数。

注意这是一个条件期望，即答案 $ans=\sum_{i=1}^{n}{E(\text{步数}\ |\ \text{最后留下的是i颜色的球})}$

设 $f_i$ 表示有 $i$ 种该颜色的球，可以列出方程 $f_i=p\times{(f_{i-1}+f_{i+1})}+(1-2p)\times{f_i}+w\ ,\ f_s=0$，$w$ 就是期望贡献。

可以发现由于这是一个条件期望，即不应该计算最后变成 $f_0$ 的概率。可以发现 $f_i$ 变成 $f_{i+1}$ 的概率和变成 $f_{i-1}$ 的概率相同，易得此时 $f_i$ 到 $f_s$ 的概率为 $\frac{i}{s}$。

也就是对于 $f_i$ 来说，这里的期望只有 $\frac{i}{s}$ 的部分对答案**有贡献**，所以 $w=\frac{i}{s}$。

接下来由于 $f_0=0$（因为不计任何贡献），可得 $f_1=\frac{(s-1)^2}{s}$，然后递推得出其他式子即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 1000000007
#define N 100010
using namespace std;
int ksm(ll a,int b=mod-2)
{
	ll ans=1;
	for(;b;b>>=1)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
int a[N],f[N];
ll sum;
int main()
{
	int n,maxn=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i],maxn=max(maxn,a[i]);
	int inv=ksm(sum);
	f[1]=1ll*(sum-1)*(sum-1)%mod*inv%mod;
	f[2]=(f[1]*2-1+mod)%mod;
	for(int i=1;i<=maxn;i++)
	f[i+1]=((2*f[i]%mod-f[i-1]+mod)%mod-1ll*(sum-1)*ksm(sum-i+mod)%mod+mod)%mod;
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+f[a[i]])%mod;
	printf("%d\n",ans);
	return 0;
}
```
