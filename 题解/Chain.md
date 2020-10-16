### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102647/problem/C)
���Ǽ�����Ŀû�� $k$ ���������ƣ�����Ҫ��ÿ��һ��������Ҫ $x$ �Ĵ��ۣ�Ҫ�� $O(n)$ �����������Ȼ��һ�� $dp$ �Ϳ��Խ���ġ�

������˵�������� $f_i,g_i$ ��ʾѡ $i$ �����Ŵ𰸺� $1$~$i$ ����һ��Ҫѡ $i$�������Ŵ𰸣����Է����� $f_i=max(g_{i-1}+x,f_{i}+a_i)$��ͬʱ����ת�ƽڵ㼴�ɡ�

������ $k$ ���������ƣ���Ҫ�������� $dp$ ��ô�죿���Է��֣���ƽ���ϻ����� $(k,k\text{���������Ž�})$������ $1\leq k\leq n$ ����һ��͹�������Է��֣���ʱ�� $x$ ���� $dp$ ���ǹ�͹���ϵĵ���б�� $k=x$ ��ֱ���нؾ������Ǹ�������

���ǿ����п��ܴ������㹲�ߣ���Ŀ���û�취��ɨ������ʱ�Ƚ�͵���ķ������Ǽ����Ŷ���Ȼ����ύ���ξͺ��ˡ�
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<ctime>
#define N 100010
#define db double
#define ll long long
using namespace std;
db f[N],g[N];
int num[N],n,m,c[N],gc[N],pre[N],gpre[N];
db rand0(db x=1e-7)
{
	db r=(double)rand()/RAND_MAX;
	while(r>x) r/=10;
	return r;
}
int check(db x)
{
	g[1]=x>0?x:0,f[1]=x;c[1]=1,gc[1]=x>0;
	pre[1]=0;gpre[1]=x>0;
	for(int i=2;i<=n;i++)
	{
		f[i]=f[i-1]+num[i]+rand0(),c[i]=c[i-1],pre[i]=i;
		if(g[i-1]+x>=f[i]) f[i]=g[i-1]+x+rand0(),c[i]=gc[i-1]+1,pre[i]=gpre[i-1];
		g[i]=g[i-1],gpre[i]=gpre[i-1],gc[i]=gc[i-1];
		if(g[i]<f[i]) g[i]=f[i],gpre[i]=i,gc[i]=c[i];
	}
	return gc[n];
}
int lf[N],rf[N];
int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++) scanf("%d",&num[i]);
	db l=-23333330,r=23333333;
	while(1)
	{
		db mid=(l+r)/2;
		int k=check(mid);
		if(k==m)
		{
			int cnt=0,u=gpre[n];
			ll ans=0;
			while(u)
			{
				int v=u;
				for(;v;v--)
				{
					if(pre[v]!=v) break;
					ans+=num[v];
				}
				lf[++cnt]=v;
				rf[cnt]=u;
				u=pre[v];
			}
			reverse(lf+1,lf+cnt+1);
			reverse(rf+1,rf+cnt+1);
			printf("%lld\n",ans);
			for(int i=1;i<=cnt;i++) printf("%d %d\n",lf[i],rf[i]);
			return 0;
		}
		if(k<m) l=mid;
		else r=mid;
	}
	return 0;
}
```
