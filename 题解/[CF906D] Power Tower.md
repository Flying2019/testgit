### [链接](https://codeforces.ml/problemset/problem/906/D)
利用扩展欧拉定理降次。
$$ a^c= \begin{cases} a^c\ \% \ p,& c<φ(p) \\a^{c\%{φ(p)}+φ(p)}, & c\geq φ(p)\end{cases} $$
可以发现幂次最多迭代$\log p$次就会全部变成1，这时直接返回1即可。所以直接从前往后暴力即可，时间复杂度$O(n\log p)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 100010
#define ll long long
using namespace std;
ll ksm(ll a,ll b,int mod)
{
	ll ans=1;
	for(;b;b>>=1)
	{
		if(b&1)
		{
			ans=ans*a;
			if(ans>=mod) ans=ans%mod+mod;
		}
		a=a*a;
		if(a>=mod) a=a%mod+mod;
	}
	return ans;
}
map<ll,ll>ph;
ll phi(ll x)
{
	if(ph.count(x)) return ph[x];
	ll &res=ph[x]=x;
	for(int i=2;i*i<=x;i++)
	if(x%i==0)
	{
		res=res/i*(i-1);
		while(x%i==0) x/=i;
	}
	if(x>1) res=res/x*(x-1);
	return res;
}
ll num[N];
ll dfs(int l,int r,int p)
{
	if(l>r || p==1) return 1;
	int res=dfs(l+1,r,phi(p));
	return ksm(num[l],res,p);
}
int main()
{
	int n,p,m;
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	scanf("%d",&m);
	while(m --> 0)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%lld\n",dfs(l,r,p)%p);
	}
	return 0;
}

```
