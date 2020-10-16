### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102658/problem/A)
### ��Ŀ����
�� $n$ ��ʯ�ӣ�ÿ�� $a_i$ �š�A��B��ȡʯ����Ϸ������A���֣�����B��������Ϸ��ʼǰ��ÿ��ʯ������ $x$ �ţ�����Ҫ��û���κ�һ��ʯ�ӱ��ù⣬�󷽰�����
### ���
����SG������Ҳ�������Ҫ�� $\sum_{x=0}^{x<\min(a_i)}[\ \bigoplus_i(a_i-x) =0\ ]$��

������λdp�����Է������û����λ����ôҪ�� $n$ ��������һλҪô��ż����1��$x$ �ĵ�ǰλΪ0����Ҫô��ż����0��$x$ �ĵ�ǰλΪ1����

������������λ��������� $x$ �� $i$ ��һλȡ1����ô��λ��һ���ǰ��� $i $ λ��С����������һ��ǰ׺��

������ $f_{i,j}$ ��ʾ�� $i$ λ����һλ��λΪ����ǰ $j$ �����䡣���Է�����λ�Ե�ǰλ��˵�൱�������������Էֱ������¼��ɡ�

�����������ֱ���û��������ܸ��Ӷ� $O(n\log a)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#define N 200010
#define M 63
#define ll long long
using namespace std;
ll f[2][N],cnt[M+10];
ll num[N];
vector<ll>v[2];
int main()
{
	int n;
	scanf("%d",&n);
	ll minn=1e18;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&num[i]);
		minn=min(minn,num[i]);
		for(int j=0;j<M;j++)
		if((num[i]>>j)&1)cnt[j]++;
	}
	f[0][0]=1;
	int u=0;
	for(int i=0;i<M;i++)
	{
		u=!u;
		int p=!u;
		memset(f[u],0,sizeof(f[u]));
		int c0=n-cnt[i],c=0;
		for(int j=0;j<=n;j++)
		{
			if(j)
			{
				if((num[j]>>i)&1) ++c0;
				else --c0,++c;
			}
			if(c0%2==0) f[u][c+c0]+=f[p][j];
			if((n-c0)%2==0) f[u][c]+=f[p][j];
		}
		v[0].clear();v[1].clear();
		int tot=0;
		for(int j=1;j<=n;j++) v[(num[j]>>i)&1].push_back(num[j]);
		for(int _=0;_<=1;_++)
			for(ll u:v[_]) num[++tot]=u;
	}
	ll res=0;
	for(int j=1;j<=n;j++) res^=num[j]-minn;
	printf("%lld\n",f[u][0]-(res==0));
	return 0;
}
```
