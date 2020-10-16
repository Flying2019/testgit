### [链接](http://codeforces.com/contest/850/problem/E)
可以发现 $ans\times 6^n$就是总方案数。

不妨钦定 $A$ 赢，最后答案 $\times 3$，可以发现，一个人如果要赢两局，就一定有 $f(A,B)=1,f(C,A)=0$。即$f(A,B)=~f(C,A)=1$

由于 $B,C$ 两人之间的相对顺序与结果无关，可以直接拆开 $A,B$ 和 $A,C$ 的相对位置（注意如果两者相同答案要乘二），可以发现这本质是一个异或卷积。稍微推一下柿子可以发现，对于结果 $g$ 的某一位，如果为1，就存在两种 $f$ 的方式得到这个异或结果，直接 $*2$ 统计结果即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 21
#define M 1<<N
#define ll long long
#define mod 1000000007
#define inv2 (mod+1)/2
using namespace std;
int f[M],g[M];
void fwt(int f[],int n,int opt)
{
	for(int l=1;l<n;l<<=1)
		for(int i=0;i<n;i+=l<<1)
			for(int j=0;j<l;j++)
			{
				int x=f[i+j],y=f[i+j+l];
				f[i+j]=(x+y)%mod;
				f[i+j+l]=(x-y+mod)%mod;
				if(opt==-1) f[i+j]=1ll*f[i+j]*inv2%mod,f[i+j+l]=1ll*f[i+j+l]*inv2%mod;
			}
}
char str[M];
int _2[N+5];
int main()
{
	int n;
	scanf("%d%s",&n,str);
	int m=1<<n;
	_2[0]=1;
	for(int i=1;i<=N;i++) _2[i]=1ll*_2[i-1]*2%mod;
	for(int i=0;i<m;i++) f[i]=str[i]-'0';
	for(int i=0;i<m;i++) g[i]=f[i^(m-1)];
	fwt(f,m,1);
	fwt(g,m,1);
	for(int i=0;i<m;i++) f[i]=1ll*f[i]*g[i]%mod;
	fwt(f,m,-1);
	int ans=0;
	for(int i=0;i<m;i++) ans=(ans+1ll*f[i]*_2[__builtin_popcountll(i)]%mod)%mod;
	printf("%lld\n",1ll*ans*3%mod);
	return 0;
}

```
