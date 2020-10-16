#### [题目链接](https://atcoder.jp/contests/arc066/tasks/arc066_c)
## 题目大意
给定一个只含加减和数字的表达式，在其中添加括号，使其值最大。
## 解题思路
显然，只有减号后面的括号会使其中表达式的值取反。

然后只有已经有左括号时才能加入右括号。

所以用$f_0$表示没有左括号，用$f_1$表示当前是负区间，$f_1$表示当前是正区间。

当当前的数是负的时，可以加入左括号转移。当存在左括号时，可以加入右括号转移。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define N 100010
#define ll long long
using namespace std;
ll f[3];
void read(ll &x)
{
	x=0;
	int ch=0,flag=1;
	for(;!isdigit(ch);ch=getchar())
	if(ch=='-') flag=-flag;
	for(;isdigit(ch);ch=getchar())
	x=x*10+ch-'0';
	x*=flag;
}
int main()
{
	int n;
	scanf("%d",&n);
	f[0]=0,f[1]=f[2]=-10000000000000ll;
	for(int i=1;i<=n;i++)
	{
		ll x;
		read(x);
		f[0]+=x;
		f[1]-=x;
		f[2]+=x;
		if(x<0)
		{
			f[2]=max(f[2],f[1]);
			f[1]=max(f[1],f[0]);
		}
		f[0]=max(f[0],f[1]);
		f[1]=max(f[1],f[2]);
	}
	printf("%lld\n",f[0]);
	return 0;
}

```
