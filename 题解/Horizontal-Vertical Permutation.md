### [����](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2997)
��ֵĹ����⡣�������ȿ��� $n$ ����������������Է�������ÿ�������Խ����ϵĵ㶼��ƥ�������У�����ÿ��������Ҫһ���Խ����ϵĵ㡣��Ȼ�����С�

���� $n$ Ϊż����������������һ�ֹ��졣

���ȣ�Ϊ�˷��㣬���ǽ����Խ���������1�����Է��֣�����������2�� $n$ ����������ǲ��֣���ô�����ǲ���ֻ�踴�Ʋ�ȫ�� $+n-1$ ���ɡ����ǲ������ǽ������ǲ���ȫ�� $-(n-1)$ ���Է��ִ�ʱ������ȫ�Գƣ����������������ÿһ�ж������С�

Ȼ���ǹ��졣���ȿ��Է��ֵ�һ�е�˳���޹ؽ�Ҫ������ֱ������1�� $n$��

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| | 1 | | | | |
| | | 1 | | | |
| | | | 1 | | |
| | | | | 1 | |
| | | | | | 1 |

�ֿ��Է��ְ�ƽ���ڸ��Խ��ߵķ�����д��һ�����еġ����Կ��Բ��Ͻ���һ�е����ְ����Խ���ƽ�ơ�

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| | 1 | 4 | 5 | 6 | |
| | | 1 | 6 | | |
| | | | 1 | | |
| | | | | 1 | |
| | | | | | 1 |

Ȼ��ת��������

| 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| 2 | 1 | 4 | 5 | 6 | |
| 3 | 4 | 1 | 6 | | |
| 4 | 5 | 6 | 1 | | |
| 5 | 6 | | | 1 | |
| 6 | | | | | 1 |

���Է��֣�������ֻ��Ҫ���ϵ���̰�ĵ�ȡ���ּ��ɡ�������̫���ˣ���ȷ�Բ�����֤����

���ֻ��Ҫ�������ǲ���ȫ�� $+n-1$ ��

���룺
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
