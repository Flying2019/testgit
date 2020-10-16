### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/C)
### ��Ŀ����
����һ������ $a_i$ �� $x$�������ѡ������ $k$ �������ཻ���䣬�������е��� $\times x$��������Ӷκ͡�
### ���
����dp���� $f_{i,j}$ ��ʾ��ǰ�� $i$ ���������($\times x$)ʱ�����Ž������ $g_{i,j}$ ��ʾ��ǰ�� $i$ û���������ʱ�����Ž����

��Ȼ�ɵ�ת�Ʒ��̣�ֱ��ת�Ƽ��ɡ����Ӷ� $O(nm)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 300010
#define M 32
#define ll long long
using namespace std;
ll f[2][M],g[2][M],val[N];
int main()
{
	int n,m,x;
	scanf("%d%d%d",&n,&m,&x);
	for(int i=1;i<=n;i++) scanf("%lld",&val[i]);
	int u=0;
	for(int i=0;i<=m;i++) f[0][i]=g[0][i]=-1000000000000ll;
	ll ans=-1000000000000ll;
	for(int i=1;i<=n;i++)
	{
		int p=u;
		u=!u;
		for(int j=0;j<=m;j++) f[u][j]=g[u][j]=-1000000000000ll;
		f[u][1]=val[i]*x,g[u][0]=val[i];
		for(int j=0;j<=m;j++)
		{
			if(j)f[u][j]=max(f[u][j],f[p][j]+val[i]*x),f[u][j]=max(f[u][j],g[p][j-1]+val[i]*x);
			g[u][j]=max(g[u][j],f[p][j]+val[i]);
			g[u][j]=max(g[u][j],g[p][j]+val[i]);
		}
		for(int j=0;j<=m;j++)
		ans=max(ans,max(f[u][j],g[u][j]));
	}
	printf("%lld\n",ans);
	return 0;
}
```
