### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102643/problem/D)
### 题目大意
有 $n$ 个长度为 $l$，字符集为 $C$ 的随机字符串，求trie树的期望点数。
### 题解
考虑对每个串单独考虑，一个串的与其他串的 $\text{lca}=i$ 的概率比较难算，考虑差分，算出 $\text{lca}\geq i$ 的概率然后差分。

显然可以发现一个串的贡献为 $1-(1-c^{-i})^{n-1}$，特别的，如果 $i=1$ 可以发现此时这个串不会和任何串有lca，结果为 $l+1$。

所以只要算出上面那玩意就好了。将上述式子化简后可得 $ans_n=\sum_{j=0}^{n-1}{n-1\choose j}(-1)^j\sum_{i=0}^l c^{-ij}$

再稍微化简式子后可得 $ans_n=l+1+(n-1)!\sum_{j=1}^{n-1}f(n-1-j)g(j)$ 形式。卷积即可。

注意这里 $ans_i$ 是差分后的数组，$ans_0=-1$，然后前缀和算一下就好了。复杂度 $O(n\log n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 1000010
#define G 3
#define mod 998244353
#define Gi (mod+1)/G
#define ll long long
#define int long long
using namespace std;
int rev[N];
int get_rev(int n)
{
	int lim=1,l=0;
	while(lim<=n*2) lim<<=1,l++;
	for(int i=1;i<lim;i++)
	rev[i]=rev[i>>1]>>1|((i&1)<<(l-1));
	return lim;
}
ll ksm(ll a,ll b=mod-2)
{
	a%=mod;
	ll r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=1ll*r*a%mod;
		a=1ll*a*a%mod;
	}
	return r;
}
void ntt(ll f[],int lim,int opt)
{
	for(int i=0;i<lim;i++)
	if(i<rev[i]) swap(f[i],f[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		ll r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
		for(int i=0;i<lim;i+=mid<<1)
			for(ll j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
			{
				ll x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
				f[i+j]=(x+y)%mod;
				f[i+j+mid]=(x-y+mod)%mod;
			}
	}
	if(opt==-1)
	{
		int inv=ksm(lim);
		for(int i=0;i<lim;i++) f[i]=1ll*f[i]*inv%mod;
	}
}
ll f[N],g[N],fac[N],inv[N];
signed main()
{
	ll n,l,c;
	scanf("%lld%lld%lld",&n,&l,&c);
	if(c==1){for(int i=1;i<=n;i++) printf("%lld\n",l%mod);return 0;}
	fac[0]=1;
	for(int i=1;i<=n*2;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[n*2]=ksm(fac[n*2]);
	for(int i=n*2-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	ll invc=ksm(ksm(c,l+1)),c1=invc;
	for(int i=1;i<=n-1;i++)
	{
		g[i]=(1-c1+mod)*ksm(1-ksm(ksm(c,i))+mod)%mod;
		c1=c1*invc%mod;
		if(i&1) g[i]=(mod-g[i])%mod;
		g[i]=1ll*g[i]*inv[i]%mod;
	}
	for(int i=0;i<=n-1;i++) f[i]=inv[i];
	int lim=get_rev(n);
	ntt(f,lim,1);
	ntt(g,lim,1);
	for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
	ntt(f,lim,-1);
	ll ans=0;
	for(int i=0;i<n;i++)
	{
		ans=(ans+1ll*f[i]*fac[i]%mod+l+1)%mod;
		if(i==0) ans=(ans-1+mod)%mod;
		printf("%lld\n",(ans+mod)%mod);
	}
	return 0;
}
```
