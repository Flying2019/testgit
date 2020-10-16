### [链接](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2997)
奇怪的构造题。。。首先考虑 $n$ 是奇数的情况。可以发现由于每个非主对角线上的点都会匹配上两行，所以每个数都需要一个对角线上的点。显然不可行。

考虑 $n$ 为偶数的情况。这里给出一种构造。

首先，为了方便，我们将主对角线上填上1。可以发现，假如我们用2到 $n$ 填好了下三角部分，那么上三角部分只需复制并全部 $+n-1$ 即可。我们不妨考虑将上三角部分全部 $-(n-1)$ 可以发现此时矩阵完全对称，而且这个矩阵满足每一行都是排列。

然后考虑构造。首先可以发现第一行的顺序无关紧要。所以直接填上1到 $n$。

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| | 1 | | | | |
| | | 1 | | | |
| | | | 1 | | |
| | | | | 1 | |
| | | | | | 1 |

又可以发现按平行于副对角线的方向填写是一定可行的。所以可以不断将第一行的数字按副对角线平移。

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| | 1 | 4 | 5 | 6 | |
| | | 1 | 6 | | |
| | | | 1 | | |
| | | | | 1 | |
| | | | | | 1 |

然后翻转到下三角

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| 2 | 1 | 4 | 5 | 6 | |
| 3 | 4 | 1 | 6 | | |
| 4 | 5 | 6 | 1 | | |
| 5 | 6 | | | 1 | |
| 6 | | | | | 1 |

可以发现，接下来只需要从上到下贪心地取数字即可。由于我太菜了，正确性并不会证明。

最后只需要将上三角部分全部 $+n-1$ 。

代码：
```cpp#include<cstdio>
#include<iostream>
#include<cstring>
#define N 1010
using namespace std;
int num[N][N],swp[N][N];
bool cnt[N*2];
#define F(i,j) num[x+i][y+j]
void make(int n,int a,int x,int y)
{
	if(n==2)
	{
		F(1,1)=F(2,2)=a+1;
		F(1,2)=F(2,1)=a+2;
		return;
	}
	int m=n/2;
//	if(n%4==0)
//	{
//		make(m,a,x,y);
//		make(m,a,x+m,y+m);
//		make(m,a+m,x,y+m);
//		make(m,a+m,x+m,y);
//		return;
//	}
//	else
	{
		for(int i=1;i<=n;i++) F(i,i)=1;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n-i+1;j++)
			F(i,j)=F(j,i)=j+i-1;
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
			if(!F(i,j))
			{
				memset(cnt,0,sizeof(cnt));
				for(int k=1;k<=i;k++) cnt[F(k,j)]=true;
				for(int k=1;k<=j;k++) cnt[F(i,k)]=true;
				int a=0;
				while(cnt[a]) ++a;
				F(i,j)=F(j,i)=a;
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) F(i,j)+=a;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	if(n==1){puts("Yes\n1");return 0;}
	if(n&1) puts("No");
	else
	{
		puts("Yes");
		make(n,0,0,0);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				num[i][j]+=n-1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) printf("%d%s",num[i][j],j!=n?" ":"\n");
	}
	return 0;
}
```
