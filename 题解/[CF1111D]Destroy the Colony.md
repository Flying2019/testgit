### [链接](https://codeforces.com/problemset/problem/1111/D)
考虑如果限制x,y本来就是相同的，那么可以发现这就是一个背包求方案数，直接dp即可。

接下来考虑如何处理x,y。~~直接回退背包~~考虑字符集其实很小，所以直接处理每对字符的情况，重新跑一边即可。复杂度 $O(|C|^2n)$。
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define N 100010
#define C 52
#define mod 1000000007
#define ll long long
using namespace std;
int fac[N],inv[N],cnt[C],ans[C][C];
int f[N],g[N];
int get_c(char c){return c>='a' && c<='z'?c-'a'+26:c-'A';}
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
char s[N];
int main()
{
	int n,m;
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) cnt[get_c(s[i])]++;
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	int res=1ll*fac[n/2]*fac[n/2]%mod;
	for(int i=0;i<C;i++) res=1ll*res*inv[cnt[i]]%mod;
	f[0]=1;
	for(int i=0;i<C;i++)
	if(cnt[i])
		for(int j=n/2;j>=cnt[i];j--) f[j]=(f[j]+f[j-cnt[i]])%mod;
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x=get_c(s[x]);
		y=get_c(s[y]);
		if(x==y) printf("%d\n",1ll*f[n/2]*res%mod);
		else if(ans[x][y]) printf("%d\n",ans[x][y]);
		else
		{
			memcpy(g,f,sizeof(f));
			for(int j=cnt[x];j<=n/2;j++) g[j]=(f[j]-g[j-cnt[x]]+mod)%mod;
			for(int j=cnt[y];j<=n/2;j++) g[j]=(g[j]-g[j-cnt[y]]+mod)%mod;
			printf("%d\n",ans[x][y]=1ll*g[n/2]*2*res%mod);
		}
	}
	return 0;
}
```
