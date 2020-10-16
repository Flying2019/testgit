### [链接](https://www.luogu.com.cn/problem/CF1163E)
先考虑假如集合存在，如何构造。很显然的一种构造是将 $[0,2^x-1]$ 用二进制表示，然后如果某一位 $i$ 是1就异或上线性基基底 $num_i$ 即可。

对于是否合法，由于每个数列都要在 $[0,2^x-1]$ 之间，而且显然这些有可能为1的位置上的基底不能为0，所以对于大小为 $2^x$ 的集合，需要满足线性基的 $0\leq num_i\leq 2^x-1 \ (i\in[0,x-1])$。

这样就需要求线性基的最小元素。可以发现原版的线性基是不能满足的，所以需要魔改一下，大概就是每次插入到某个线性基基底，在交换前特判一下两者哪一个大，如果新插入的大就交换一下。

然后直接输出即可。复杂度 $O(n\log n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 200010
#define M 31
using namespace std;
int num[M+2],p[M+2];
void insert(int x)
{
	int u=x;
	for(int i=M;i>=0;i--)
	if((x>>i)&1)
	{
		if(!num[i]){num[i]=x,p[i]=u;return;}
		if(p[i]>u) swap(num[i],x),swap(u,p[i]);
		x^=num[i];
	}
}
int a[N];
void get_d(int x,int &d)
{
	if(x==-1)return;
	get_d(x-1,d);
	printf("%d ",d^=p[x]);
	get_d(x-1,d);
}
int main()
{
	memset(p,64,sizeof(p));
	int n,res=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),insert(a[i]);
	while(num[res]) res++;
	--res;
	while(res>=0 && p[res]>=1<<(res+1)) res--;
	printf("%d\n",res+1);
	int swp=0;
	printf("%d ",0);
	get_d(res,swp);
	return 0;
}
```
