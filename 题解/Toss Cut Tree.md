### [链接](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2994)
考虑由于期望的线性性和欧拉公式，可以将原答案变成点点，点边，边点，边边的期望，分别dp即可。

复杂度 $O(n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<set>
#define N 200010
#define mod 998244353
#define ll long long
using namespace std;
ll ksm(ll a,ll b=mod-2)
{
	if(b<0) return 0;
	ll r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=r*a%mod;
		a=a*a%mod;
	}
	return r;
}
ll fac[N],inv[N];
set<int>a[N],b[N];
ll C(int a,int b){return a<b?0:fac[a]*inv[b]%mod*inv[a-b]%mod;}
int main()
{
	int n;
	scanf("%d",&n);
	if(n==1){puts("0");return 0;}
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x].insert(y);
		a[y].insert(x);
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		b[x].insert(y);
		b[y].insert(x);
	}
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	ll ans=0;
	for(int i=1;i<=n;i++)
	ans+=(C(n,i)*i%mod*(n-i)%mod-2*C(n-2,i)*i%mod*(n-1)%mod+mod)%mod;
	ll c=ksm(2,n-4);
	for(int x=1;x<=n;x++)
		for(int y:a[x])
		if(x<=y) ans=(ans+c*(n-1-b[x].size()-b[y].size()+b[x].count(y)+mod))%mod;
	ans=(ans%mod+mod)%mod;
	printf("%lld\n",ans*ksm(ksm(2,n))%mod);
	return 0;
}
```
