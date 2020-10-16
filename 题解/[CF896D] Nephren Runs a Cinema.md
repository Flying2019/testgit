### [链接](http://codeforces.com/problemset/problem/896/D)
考虑组合计数，可以发现我们把付50看做左括号，付100看做右括号。

然后我们可以先排好不付钱的，然后把括号往里面插。那么按照套路转换成二维平面问题，也就是不能越过 $y=x$ 的线。

也就是现在只要求 $(0,0)$ 到 $(n,[l,r])$ 的合法方案即可。

考虑容斥。即我们显然可以用不合法的减去合法的。这里有一个套路，即对于 $(p,q),(p\geq q)$，我们用 $(p,q)$ 的所有方案减去 $(q-1,p+1)$ 的所有方案即可。

证明可以考虑，$(0,0)$ 到 $(q-1,p+1)$ 一定会到达 $y=x+1$，而我们把穿过的上部分翻着下来，恰好对应一条 $(0,0)$ 到 $(p,q)$ 且穿过 $y=x$ 的线。

而所有方案显然就是组合数。但是这里模数不一定是质数怎么办。

我们考虑对 $mod$ 分解质因数，然后对于每个数字，提取其中的与 $mod$ 互质的因子。

对于剩下部分，由于乘除对应到指数上就是加减，所以对应项处理即可。

复杂度 $O(n\log a)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int phi,mod;
int ksm(int a,int b=phi-1)
{
	int r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=1ll*r*a%mod;
		a=1ll*a*a%mod;
	}
	return r;
}
int pr[N],cnt;
ll sm[N][30],fac[N],inv[N];
void pre_work(int n)
{
	int u=mod;
	phi=mod;
	for(int i=2;i*i<=u;i++)
	if(!(u%i)){phi=phi/i*(i-1),pr[++cnt]=i;while(u%i==0) u/=i;}
	if(u>1) phi=phi/u*(u-1),pr[++cnt]=u;
    fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		memcpy(sm[i],sm[i-1],sizeof(sm[i]));
        int p=i;
        for(int j=1;j<=cnt;j++)
        	for(;p%pr[j]==0;p/=pr[j]) sm[i][j]++;
		fac[i]=1ll*fac[i-1]*p%mod,inv[i]=(fac[i]?ksm(fac[i]):0);
    }
}
ll C(int n,int m)
{
	if(m<0 || n<m) return 0;
	if(m==0) return 1;
	ll res=1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
	for(int i=1;i<=cnt;i++)
		res=1ll*res*ksm(pr[i],sm[n][i]-sm[m][i]-sm[n-m][i])%mod;
	return res;
}

int main()
{
	int n,l,r;
	scanf("%d%d%d%d",&n,&mod,&l,&r);
	pre_work(N-10);
	r=min(n,r);
	int ans=0;
	for(int i=0;i<=n-l;i++)
	{
		ll res=(C(n-i,(n-i-l)>>1)-C(n-i,(n-i-r-1)>>1)+mod)%mod;
		ans=(ans+1ll*res*C(n,i))%mod; 
	}
	printf("%d\n",ans);
	return 0;
}
```
