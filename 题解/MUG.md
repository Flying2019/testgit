### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102643/problem/A)
显然dp。可以发现当前选择只依赖于上一轮的选择，而上一轮只有放右手/放左手/不放，用 $f_i,g_o,h_i$ 分别表示，直接dp即可。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 8
#define M 1000010
#define int long long
using namespace std;
int f[M],g[M],h[M],s[M],ps[M];//f:R g:L h:No
signed main()
{
	int n,p1,p2,p3;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&s[i]),s[i]/=100;
	for(int i=1;i<=n;i++) scanf("%lld",&ps[i]);
	scanf("%lld%lld%lld",&p1,&p2,&p3);
	f[1]=g[1]=s[1]*100,h[1]=0;
	int u=0,ans=0;
	for(int i=2;i<=n;i++)
	{
		h[i]=max(f[i-1],g[i-1]);
		f[i]=g[i]=h[i-1]+s[i]*100;
		f[i]=max(f[i],f[i-1]+s[i]*p3);
		if(ps[i]>=ps[i-1]) f[i]=max(f[i],g[i-1]+s[i]*100);
		else f[i]=max(f[i],g[i-1]+s[i]*p2);
		if(ps[i]<=ps[i-1]) g[i]=max(g[i],f[i-1]+s[i]*100);
		else g[i]=max(g[i],f[i-1]+s[i]*p1);
	}
	printf("%lld\n",max(max(f[n],g[n]),h[n]));
	return 0;
}
```

