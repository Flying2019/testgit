### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102647/problem/D)
### ��Ŀ����
$n��n$ �����ϵ� $(n+1)^2$ ���㣬��� $(0,0)$ ������ֱ�ߣ�ǡ��ͨ�� $m$ ����ķ�������

�������������ǲ�ͬ�ģ����ҽ�������һ�������ڷ���A�����ڷ���B��
### ���
�������ǲ������������� $y=x$ ����ֱ�ߵ��·��ߣ����Է�����󽫴� $\times 2$ ���ɣ������� $y=x$ ֱ�����У���

���Է��֣����������� $\tan\alpha=\frac{b}{a}\ (\gcd(a,b)=1\ , \ a>b)$ �ķ����ߣ���ô�����ĵ�������� $\lfloor\frac{n}{a}\rfloor+1$��

�������ǿ��Եõ�ʽ�� $ans=\sum_{i=2}^{n}{\sum_{j=1}^{i-1}[\ \gcd(i,j)=1\ ][\ \lfloor\frac{n}{i}\rfloor}+1=m\ ]$�����Է��ֱ���͵�ʽ�ӱ��ʾ��ǽ� $[\ \lfloor\frac{n}{i}\rfloor+1=m\ ]$ ���� $��(i)$ �顣

���� $ans=\sum_{i=2}^{n}��(i)[\ \lfloor\frac{n}{i}\rfloor+1=m\ ]$��

���Է��֣����Ϻ����Ǹ�ʽ�ӵ� $i$ ��һ�����䣬���ʾ���һ�� $��(i)$ �ĺͣ�����ɸ�� $��(i)$ ��ǰ׺�ͼ��ɡ����Ӷ� $O(n+T)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define N 5000010
#define ll long long
int phi[N],pr[N],tot;
bool p[N];
ll sum[N];
void init(int n)
{
	for(register int i=2;i<=n;i++)
	{
		if(!p[i])
		{
			pr[++tot]=i;
			phi[i]=i-1;
		}
		for(register int j=1;j<=tot && 1ll*i*pr[j]<=n;j++)
		{
			int k=i*pr[j];
			p[k]=1;
			if(i%pr[j]) phi[k]=phi[i]*(pr[j]-1);
			else{phi[k]=phi[i]*pr[j]; break;}
		}
	}
}

int main()
{
	init(N-10);
	for(register int i=1;i<=N-10;i++) sum[i]=phi[i]+sum[i-1];
	int t;
	scanf("%d",&t);
	while(t --> 0)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		++n;
		if(m==n){puts("3");continue;}
		if(m==1){puts("1");continue;}
		int l=(n-1)/m,r=(n-1)/(m-1);
		printf("%lld\n",(sum[r]-sum[l])*2);
	}
	return 0;
}
```
