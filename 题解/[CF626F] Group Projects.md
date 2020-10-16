### [����](https://codeforces.com/problemset/problem/626/F)
������·������ֻ���Ӽ��й�������

���Է��֣�������Ŀ��ת���ɣ��������� $n$ ���㣬����Էֳ������飬���峤��Ϊÿ�����˵���Ҷ˵㡣ÿ��ĳ��ȺͲ����� $k$����������п��з�����������

���Է��֣���������ĳ������˵�����е���˵�λ�ò�����Ҫ��ֻ��Ҫ֪���ж��������˵���Ҷ˵㾭�������ɡ�

�����Ϳ���dp�ˡ��� $f_{i,j,k}$ ��ʾǰ $i$ ���㣬$j$ ���黹û���Ҷ˵㣬�ܳ�Ϊ $k$ �ķ�������

���Է��֣�����ĳ���� $i$�����Խ��У�

1. �����κβ����������Ĵ����� $j\times (a_i-a_{i-1})$�������� $\times (j+1)$��
2. ��Ϊһ����˵㡣�����Ĵ����� $j\times (a_i-a_{i-1})$�������� $\times 1$��
2. ��Ϊһ���Ҷ˵㡣�����Ĵ����� $j\times (a_i-a_{i-1})$�������� $\times (j+1)$��

�ֱ�ת�Ƽ��ɡ����Ӷ� $O(n^2m)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 1010
#define ll long long
#define mod 1000000007
using namespace std;
int v[N];
int f[N][N][M];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	sort(v+1,v+n+1);
	for(int i=0;i<n;i++) v[i]=v[i+1]-v[i];
	f[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=m-v[i]*j;k++)
			{
				f[i+1][j][k+v[i]*j]=(f[i+1][j][k+v[i]*j]+1ll*f[i][j][k]*(j+1)%mod)%mod;
				f[i+1][j+1][k+v[i]*j]=(f[i+1][j+1][k+v[i]*j]+f[i][j][k])%mod;
				if(j) f[i+1][j-1][k+v[i]*j]=(f[i+1][j-1][k+v[i]*j]+1ll*f[i][j][k]*j%mod)%mod;
			}
	int ans=0;
	for(int i=0;i<=m;i++) ans=(ans+f[n][0][i])%mod;
	printf("%d\n",ans);
	return 0;
}
```
