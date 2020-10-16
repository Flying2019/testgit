### [链接](http://codeforces.com/problemset/problem/264/D)
奇怪的字符串匹配。

我们用点 $(x,y)$ 表示两个字符串中第一个匹配到 $x$，第二个匹配到 $y$，那么这就变成了一张二维的图。

考虑什么情况下会导致某个点不可达：可以发现，如果出现 $\texttt{RG},\texttt{GR}$ 这样的串，那么这里会出现一个不可达的点。

可以发现只有这种情况会导致**该点**不可达。也就是说一个点 $(x,y)$ 不可达，那么一定没有一条 $(x-1,y-1)\rightarrow (x,y)$ 的边。

也就是说，对于剩下的点，我们可以直接贪心处理，维护一下前缀和即可。

复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 1000010
using namespace std;
char str[N];
int s[N],t[N];
ll ans;
int f[N][8];
inline int sv(int x,int y){return (x>y)*4+x+y;}
int main()
{
	int n,m;
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++) s[i]=str[i]=='R'?0:(str[i]=='G'?1:2);
	for(int i=2;i<=n+1;i++)
	{
		memcpy(f[i],f[i-1],sizeof(f[i]));
        if(i<=n && s[i-1]!=s[i]) f[i][sv(s[i-1],s[i])]++;
	}
	scanf("%s",str+1);
	m=strlen(str+1);
	for(int i=1;i<=m;i++) t[i]=str[i]=='R'?0:(str[i]=='G'?1:2);
	int l=1,r=1;
	for(int i=1;i<=m;i++)
	{
		if(i>1 && t[i]!=t[i-1]) ans-=f[r][sv(t[i],t[i-1])]-f[l][sv(t[i],t[i-1])];
		for(;r<=n && s[r]!=t[i];r++);ans+=r-l+(r<=n);
		if(r<=n) ++r;
		if(l<r && s[l]==t[i]) ++l;
	}
	printf("%lld\n",ans);
	return 0;
}
```
