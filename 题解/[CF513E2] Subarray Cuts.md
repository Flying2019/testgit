### [链接](http://codeforces.com/problemset/problem/513/E2)
考虑一个性质：假如我们把绝对值去掉，那么最后有效的成分只有极大值($s_{i-1}\leq s_{i}\geq s_{i+1}$)或极小值($s_{i-1}\geq s_{i}\leq s_{i+1}$)。

可以发现，由于绝对值符号必然不为负，假如我们将一个极小值误认为极大值，或是将一个不做贡献的值误认为极小值，都会导致答案减小。

也就是说，我们可以抛开相对大小关系。假如我们钦定了一个值为极大值，而事实上最后它不是极大值，那么其结果一定不比正确结果优。

所以我们令 $f_{i,j,0/1/2/3}$ 表示前 $i$ 个数字分 $j$ 段，当前段在极大值/极大值到极小值(不选)/极小值/极小值到极大值(不选)。

分别dp即可。特别的，由于题目要求恰好 $k$ 段，所以最后有可能在极大值到极小值选一些无用的段。这里一样也不用考虑真实的大小关系，因为错误的结果一定不会由于正确的结果。对于开头结尾需要特殊处理。

复杂度 $O(nk)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 30010
#define M 210
using namespace std;
int f[N][M][4],a[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int _=0;_<4;_++) f[i][j][_]=-100000000;
	for(int i=0;i<=n;i++)
		for(int _=0;_<4;_++) f[i][0][_]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int t=1+(j!=1 && j!=m);
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j-1][3])-t*a[i];
			f[i][j][1]=max(f[i-1][j][1],f[i][j][0]);
			f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1])+t*a[i];
			f[i][j][3]=max(f[i-1][j][3],f[i][j][2]);
			if(t==2) f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]),f[i][j][3]=max(f[i][j][3],f[i-1][j-1][3]);
		}
	printf("%d\n",max(f[n][m][1],f[n][m][3]));
	return 0;
}
```
