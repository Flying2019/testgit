### [链接](http://codeforces.com/problemset/problem/578/D)
经典计数。

考虑 $\operatorname{lcs}$ 等价于抽取一个字母，然后在任意位置放置一个其他字母。所以一次的方案数为 $n\times(m-1)$。

考虑记重，首先一段相同字母只能记一次。然后考虑如果有一段极长的段是 $\texttt{ababab}$ 这样的，显然把 $\texttt{a}$ 放在末尾和把 $\texttt{b}$ 放在开头是一样的。这部分贡献也要减掉。

总复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
char s[N];
int n,m;
ll ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) ans+=1ll*n*(m-1)*(int)(s[i]!=s[i-1]);
	int l=1;
	for(int i=2;i<=n;i++)
	if(l==1) l+=s[i]!=s[i-1];
	else if(s[i]==s[i-2]) l++;
	else ans-=l*(l-1)/2,l=1+(s[i]!=s[i-1]);
	ans-=1ll*l*(l-1)/2;
	printf("%lld\n",ans);
	return 0;
}
```
