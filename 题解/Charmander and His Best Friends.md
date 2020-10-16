### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/F)
### 题目大意
构造一个序列，满足 $\forall 1\leq j\leq i\leq n-j$，有 $2\times a_{i}\neq a_{i-j}+a_{i+j}$。
### 题解
先令 $a_i=i$。很显然这样是不符合条件的，所以我们要调整。

怎么办？直接将奇偶分组，奇数提前，偶数放后面。

很明显，无论怎么将左右打乱，都不存在一组 $i-j< \frac n 2 < i+j$ 违反上述条件。因为这样 $a_{i-j}+a_{i+j}$ 必然为奇数，显然不符合条件。

同理，将左右区间按上述方式递归处理，得到的数列也不可能存在一个跨过中间的 $i-j,i+j$ 违反条件。

所以正确性显然。复杂度 $O(n\log n)$。（忽然发现和FFT的rev数组如出一辙）。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 50010
using namespace std;
int num[N],swp[N];
void work(int a[],int n)
{
	if(n==1) return;
	int v=(n+1)>>1;
	if(n&1)
	{
		for(int i=0;i<v;i++) swp[i]=a[i*2];
		for(int i=0;i<v-1;i++) swp[i+v]=a[i*2+1];
		for(int i=0;i<n;i++) a[i]=swp[i];
		work(a,v);
		work(a+v,v-1);
	}
	else
	{
		for(int i=0;i<v;i++) swp[i]=a[i*2];
		for(int i=0;i<v;i++) swp[i+v]=a[i*2+1];
		for(int i=0;i<n;i++) a[i]=swp[i];
		work(a,v);
		work(a+v,v);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) num[i]=i+1;
	work(num,n);
	for(int i=0;i<n;i++) printf("%d ",num[i]);
	return 0;
}
```
