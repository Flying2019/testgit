### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102666/problem/F)
### 题目大意
有 $n$ 个点，对于每个 $0\leq m\leq \frac{n(n-1)}2$，求 $n$ 个点 $m$ 条边的联通块数量。
### 题解
首先考虑不联通的情况，令 $g_{n,m}$ 表示 $n$ 个点 $m$ 条边的方案数，显然有 $\displaystyle g_{n,m}=\binom{\frac{n(n-1)}{2}}{m}$。

接下来考虑答案，不妨用 $f_{n,m}$ 表示 $n$ 个点 $m$ 条边的联通块方案数，可以发现有 
$$f_{n,m}=g_{n,m}-\sum_{i=1}^{n-1}\binom{n-1}{i-1}\sum_{j=1}^{m}f_{i,j}\times g_{n-i,m-j}$$

可以理解成，全部联通的方案数是所有方案数减去不全联通的方案数。而不全联通可以看成强行划出 $i$ 个点 $j$ 条边的联通块。

然而直接计算上述式子是 $O(n^5)$。

可以发现后面那个式子是一个卷积形式，直接NTT，$O(n^4\log n)$。

还是会T啊！考虑我们没必要每次都处理 $\text{DFT}$ 和 $\text{IDFT}$，直接保留 $f_{i,j}$ 的 $\text{DFT}$ 形式即可。

由于还是有点慢，需要卡一下常才能过。

复杂度 $O(n^4)$。
```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#define N 110
#define M 20010
#define G 3
#define mod 998244353
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define Gi (mod+1)/G
using namespace std;
int rev[M];
int get_rev(int n)
{
	int lim=1,l=0;
	while(lim<=n*2) lim<<=1,l++;
	for(int i=1;i<lim;i++)
	rev[i]=rev[i>>1]>>1|((i&1)<<(l-1));
	return lim;
}
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
void ntt(int f[],int lim,int opt)
{
	for(int i=0;i<lim;i++)
	if(i<rev[i]) swap(f[i],f[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		int r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
		for(int i=0;i<lim;i+=mid<<1)
			for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
			{
				int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
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
int f[N][M],g[N][M],h[M],fac[M],inv[M];
int calc(int n){return n*(n-1)/2;}
int C[N][N];
inline int Cf(int x,int y){return y==0?1:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main()
{
    int n;
    scanf("%d",&n);
    int m=calc(n);
    fac[0]=1;
	C[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        C[i][0]=1;
    	for(int j=1;j<=n;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
    for(int i=1;i<=m;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[m]=ksm(fac[m]);
    for(int i=m-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=calc(i);j++) g[i][j]=Cf(calc(i),j);
    int lim=get_rev(m);
    for(int i=1;i<=n;i++) ntt(g[i],lim,1);
    for(register int i=1;i<=n;i++)
    {
        for(register int j=0;j<lim;j++) f[i][j]=g[i][j],h[j]=0;
        for(register int j=0;j<lim;j++)
        	for(register int t=1;t<i;t++) h[j]=(h[j]+1ll*C[i-1][t-1]*f[t][j]%mod*g[i-t][j])%mod;
        for(register int j=0;j<lim;j++) f[i][j]=(f[i][j]-h[j]+mod)%mod;
    }
    ntt(f[n],lim,-1);
    for(int i=0;i<=m;i++) printf("%d\n",f[n][i]);
	// printf("%d",clock());
    return 0;
}
```
