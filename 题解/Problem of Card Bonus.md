### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102657/problem/E)
### ��Ŀ����
�� $n$ ����Ʒ��ÿ����Ʒ��������ֵ $a_i,b_i,c_i$���������־�Ϊ�Ǹ���������֤ $a_i\leq b_i(1\leq i \leq n)$��

����һ���� $P$����ѡ��һ����Ʒ���� $S$�������� $\sum_{i\in S}a_i\leq P\leq \sum_{i\in S}b_i$ ʱ $\sum_{i\in S}c_i$ ����Сֵ��
### ���
����dp���� $f_{i,j}$ ��ʾǰ $i$ ���������� $\sum_{i\in S}a_i\leq j\leq \sum_{i\in S}b_i$ ʱ $\sum_{i\in S}c_i$ ����Сֵ��

��Ȼ��֪ת��
$$f_{i,j}=\min(f_{i-1,j},\ \min_{k\in[\ j-b_i\ ,\ j-a_i\ ]}(f_{i-1,k}+c_i))$$
���Է��֣��������� $k\in[\ j-b_i\ ,\ j-a_i\ ]$ �ĵ���ת�ƺ�һ������ $f_{i,j}$ �Ķ��塣ֱ��ת������ȷ�ġ�

�������ڶ���ÿ�� $i$������ $[\ j-b_i\ ,\ j-a_i\ ]$ �ĳ���ʱȷ���ģ�ֱ�ӵ������м��ɡ����Ӷ� $O(nP)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 10010
#define ll long long
using namespace std;
int a[N],b[N],c[N];
int n,P;
ll q[N*2];
int pos[N*2],ql,qr;
ll f[2][N];
int main()
{
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		scanf("%d%d",&n,&P);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		for(int i=1;i<=n;i++) scanf("%d",&c[i]);
		memset(f,60,sizeof(f));
		f[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			int u=i&1,p=!u;
			ql=qr=0;
			memset(f[u],60,sizeof(f[u]));
			for(int j=0;j<=P;j++)
			{
				if(j<a[i]){f[u][j]=f[p][j];continue;}
				while(qr>ql && q[qr]>=f[p][j-a[i]]) --qr;
				q[++qr]=f[p][j-a[i]]; pos[qr]=j-a[i];
				if(pos[ql+1]<j-b[i]) ++ql;
				f[u][j]=min(f[p][j],q[ql+1]+c[i]);
			}
		}
		printf("%lld\n",f[n&1][P]>=1e15?-1:f[n&1][P]);
	}
	
	return 0;
}
```
