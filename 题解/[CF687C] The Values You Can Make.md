### [����](https://codeforces.com/problemset/problem/687/C)
����dp�����Է������������ÿöӲ��������״̬������ѡ�У���ѡ�е����ڼ����У���ѡ�����ڼ����С�

���Է��� $n,m$ �ǳ���С������ֱ��dp���� $f_{i,j,k}$ ��ʾ���� $i$ öӲ�ң���ѡ�е�Ӳ���ܼ�ֵΪ $j$��������Ӳ���ܼ�ֵΪ $k$ �Ƿ���С�

�ռ���ܻ�ը����Ҫ�������顣

����Ȼ���dp������ $O(n^3)$ �ģ���bitset�Ż����Դﵽ $O(\frac{n^3}{\omega})$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<bitset>
#define N 1010
#define M 510
using namespace std;
bitset<N> f[2][M],o;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	f[0][0][0]=true;
	for(int i=0;i<=k;i++) o[i]=1;
	for(int i=1;i<=n;i++)
	{
		int c;
		int u=i&1,p=!u;
		scanf("%d",&c);
		for(int j=0;j<=k;j++) f[u][j]=f[p][j];
		for(int j=0;j<=k-c;j++)
		f[u][j+c]|=(f[p][j]|(f[p][j]<<c))&o;
	}
	int cnt=0;
	for(int i=0;i<=k;i++)
	if(f[n&1][k][i]) cnt++;
	printf("%d\n",cnt);
	for(int i=0;i<=k;i++)
	if(f[n&1][k][i]) printf("%d ",i);
	return 0;
}

```

