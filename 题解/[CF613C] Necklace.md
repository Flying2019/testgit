### [链接](http://codeforces.com/problemset/problem/613/C)
第一眼以为是一个字符串题，结果发现是一个构造题。

考虑什么情况下会出现多个回文串。可以发现，对于从 $l$ 处切断构成的回文串，必然有 $[1,2\times l],[2\times l+1,n]$ 均为回文串。

那么这样答案很明显了：只有这个字符串的循环节尽可能小的情况下，这样的 $l$ 才会最多。

考虑每一个循环节内的构造。我们只需要保证这是一个回文串即可。

首先假如有多个奇数字符需要被放入，显然不可行，答案就是0。

对于剩余情况，答案就是 $\gcd(a_i)$。

如果只有1个奇数数量的字符，显然把偶数位字符对称放两边，奇数位字符放中间。

否则直接把偶数位字符对称放两边。这种情况下尽管循环节多出一个2，但是对称轴也会多乘上一个2。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int num[27];
int main()
{
	int n;
	scanf("%d",&n);
	int g=0;
	int cnt=-1;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&num[i]);
		g=gcd(g,num[i]);
		if(num[i]&1) cnt=(cnt==-1?i:-2);
	}
	if(cnt==-2)
	{
		puts("0");
		for(int i=0;i<n;i++)
			for(int j=1;j<=num[i];j++) putchar('a'+i);
		return 0;
	}
	printf("%d\n",g);
	for(int i=0;i<n;i++) num[i]/=g;
	if(cnt==-1)
	{
		for(int i=1;i<=g/2;i++)
		{
			for(int j=0;j<n;j++)
				for(int k=1;k<=num[j];k++)
					putchar('a'+j);
			for(int j=n-1;j>=0;j--)
				for(int k=1;k<=num[j];k++)
					putchar('a'+j);
		}
		return 0;
	}
	else
	{
		for(int i=1;i<=g;i++)
		{
			for(int j=0;j<n;j++)
			if(j!=cnt)
				for(int k=1;k<=num[j]/2;k++)
				putchar('a'+j);
			for(int k=1;k<=num[cnt];k++) putchar('a'+cnt);
			for(int j=n-1;j>=0;j--)
			if(j!=cnt)
				for(int k=1;k<=num[j]/2;k++)
				putchar('a'+j);
		}
	}
	return 0;
}
```
