### [链接](http://zhengruioi.com/contest/684/problem/1492)
由于有 $3k^2-3^k+1\equiv 1(mod 6)$。

所以 $ans\equiv n(mod 6)$。

根据提示，对于 $n\equiv 1$ 和 $n \equiv 2$ 的情况单独处理即可。其余情况均只有一种情况。

而 $ans=1$ 直接计算，$ans=2$ 直接双指针扫即可。复杂度 $O(\sqrt n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll calc(int k){return 3ll*k*k-3ll*k+1;}
int main()
{
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		ll n;
		scanf("%lld",&n);
		if(n%6==1)
		{
			int k=sqrt((n-1)/3)+1;
			while(calc(k)>n) k--;
			if(calc(k)==n) puts("1");
			else puts("7");
		}
		else if(n%6==2)
		{
			int l=0,r=sqrt((n-2)/3)+1;
			bool can=false;
			for(l=0;calc(l)<n;l++)
			{
				while(calc(l)+calc(r)>n) r--;
				if(calc(l)+calc(r)==n) can=true;
			}
			if(can) puts("2");
			else puts("8");
		}
		else printf("%d\n",(n-1)%6+1);
	}
	return 0;
}
```
