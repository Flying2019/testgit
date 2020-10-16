### [链接](https://codeforces.com/problemset/problem/1198/F)
很有意思的一道题。

首先质因数分解，可以发现每个数字最多只有9个质因子。也就是说我们要把所有数字分成两个集合，每个集合对于每个质因子至少有一个数字没有该质因子。

考虑如何处理。显然存在一个错误的贪心：假如某个数字加入1集合能减小gcd，那么就加入1，否则就加入2。这个连样例2都过不去。

我们考虑这种贪心什么时候是错的。即某个数字加入1不可行，不如另一个数字加入1，这个数字加入2。

比如样例2中15就是被错误加入1，实际上没有用处。

但是这样可以看出，成功率其实蛮高的。因为这样的错误的数字一定不超过8个。也就是我们要求的有序数对不超过8对。

那么期望有 $\frac 1 {2^8}$ 概率能解决问题。事实上这类有序数对在某些地方还是重复的，成功的概率其实远大于这个值。

重复100次就足够了。时间复杂度 $O(100n\log a)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int num[N],id[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
bool _2[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]),id[i]=i;
	for(int _=0;_<100;_++)
	{
		random_shuffle(id+1,id+n+1);
		int g1=num[id[1]],g2=0;_2[id[1]]=false;
		for(int i=2;i<=n;i++)
		if(num[id[i]]%g1==0) g2=gcd(num[id[i]],g2),_2[id[i]]=true;
		else g1=gcd(g1,num[id[i]]),_2[id[i]]=false;
		if(g1==1 && g2==1){puts("YES");for(int i=1;i<=n;i++) printf("%d ",1+(int)_2[i]);return 0;}
	}
	puts("NO");
	return 0;
}
```
