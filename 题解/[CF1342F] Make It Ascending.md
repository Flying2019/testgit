### [链接](https://codeforces.com/problemset/problem/1342/F)
毒瘤状压dp。

看到 $n$ 很小，而且不超过18，考虑往 $O(n^?2^n)$ 或者 $O(n^?3^n)$ 方面想。

先分析一波性质。可以发现加的本质是把一堆数字合并在一起，但是最后必须得放在某一位上。

这类似于子集划分，所以我们用划分块作贪心。即 $f_{i,u,s}$ 表示当前第 $i$ 块，$u$ 是上一个块的合并点，$s$ 集合的数字已经处理完了，记录的是满足条件的块的最小值（因为要求单调递增，显然能小就小）。

然后很明显，我们在剩下的集合中枚举一个子集作为这个块，然后按照贪心，我们选择一个 $>u$ 的最靠前的位置作为合并点。

考虑为什么这么贪心正确。首先根据无后效性合并的块一定比之前块大，所以 $>u$，而后面的块也同理，所以尽可能靠前可以给后面的块尽可能多得空间。

而这个等同于第一个为0的位置，直接用库函数中的 $\texttt{__builtin_ctz(t>>u)}$ 可以方便求解。

最后统计方案就直接记录方案即可。复杂度 $O(n^23^n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 16
#define M 1<<N
#define inf 100000000
using namespace std;
struct stt{
	int t,u,s;
	stt(int T=0,int U=0,int S=0):t(T),u(U),s(S){}
}pre[N][N][M];
int f[N][N][M],a[N],g[M],id[N];
int main()
{
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&a[i]);
		int m=(1<<n)-1;
		for(int s=0;s<=m;s++) g[s]=0;
		for(int s=0;s<=m;s++)
			for(int i=0;i<n;i++)
			if(s&(1<<i)) g[s]+=a[i];
		for(int s=0;s<=m;s++)
			for(int i=0;i<=n;i++)
				for(int j=0;j<=n;j++) f[i][j][s]=inf;
		f[0][0][0]=0;
		for(int i=0;i<n;i++)
			for(int u=0;u<n;u++)
				for(int s=0;s<=m;s++)
				if(f[i][u][s]<inf)
					for(int t=s^m;t;t=(t-1)&(s^m))
					if(g[t]>f[i][u][s] && (t>>u))
					{
						int v=u+__builtin_ctz(t>>u)+1;
						if(f[i+1][v][s|t]>g[t])
						{
							f[i+1][v][s|t]=g[t];
							pre[i+1][v][s|t]=stt(i,u,s);
						}
					}
		stt u(-1,-1,-1),v;
		for(int i=n;i>=1 && u.t==-1;i--)
			for(int j=1;j<=n;j++)
				if(f[i][j][m]<inf){u=stt(i,j,m);break;}
		printf("%d\n",n-u.t);
		for(int i=0;i<n;i++) id[i]=i+1;
		for(;u.t;u=v)
		{
			v=pre[u.t][u.u][u.s];
			int t=u.s^v.s;
			for(int i=0;i<n;i++)
			if((t&(1<<i)) && i!=u.u-1)
			{
				printf("%d %d\n",id[i],id[u.u-1]);
				for(int j=i+1;j<n;j++) id[j]--;
			}
		}
	}
	return 0;
}
```
