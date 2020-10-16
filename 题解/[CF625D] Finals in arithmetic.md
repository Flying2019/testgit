### [链接](https://codeforces.com/problemset/problem/625/D)
贪心处理，不需要什么数位dp。

假如没有进位，那么两个回文串的和一定还是一个回文串，重点在于进位。

那么倒过来想，如果和串的两个对应位置不同，那么一定发生了进位。

对于每一个位置 $(l,r)$，很明显只有两种进位：$r$ 接受 $r-1$ 的进位，$l$ 给 $l+1$ 退位。

所以对这些情况分别讨论即可。很明显这些不同的进位方式组合得到的是不同的结果，分别倒退即可。

特别的，当最后只剩下一个位置时只需要判断该位奇偶性并除以2即可。

还有当首位为1时，注意特判位数少一的情况。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int num[N],ans[N];
char s[N];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++) num[i]=s[i]-'0';
	int l=1,r=n;
	if(num[l]!=num[r])
	{
		num[l]--;
		num[l+1]+=10;
		if(num[l]==0) l++;
	}
	for(;l<=r;l++,r--)
	{
		if(num[l]!=num[r])
		{
			if(num[l]-num[r]>=10) num[r]+=10,num[r-1]--;
			if(num[l]-num[r]==1) num[l]--,num[l+1]+=10;
		}
		if(num[l]!=num[r]){puts("0");return 0;}
		if(l!=r) ans[l]=num[l]-num[r]/2,ans[r]=num[r]/2;
		else
		{
			if(num[l]&1){puts("0");return 0;}
			ans[l]=num[l]/2;
		}
	}
	for(int i=1;i<=n;i++)
	if(ans[i]<0 || ans[i]>9){puts("0");return 0;}
	
	int i=1;
	for(;!ans[i];i++);
	for(;i<=n;i++) printf("%d",ans[i]);
	return 0;
}
```
