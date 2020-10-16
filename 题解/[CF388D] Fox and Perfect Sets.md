### [����](https://codeforces.com/contest/388/problem/D)
������λdp��

�� $f_{i,j,k}$ ��ʾ�ӵ� $j$ λ�����λ�Ѿ�ѡ�� $j$ ������ͨ�� $+2^i$ �Ƿ񳬹� $n$��

���Է���ͨ���������ۿ��Դ������Ӧ�����������˵�������жϵ�ǰ $i$ �Ƿ���һ���µĻ����������ô��һλֻ��һ��ѡ�� $2^i$��������һλ���Ը���ǰ��λ���Ƴ��������� $2^j$��

��ô���ڿ��ܳ�������������ȶ��� $n$ ��һλ�������ۡ���� $n$ ��һλΪ0����ô��һλ�Ͳ�������ˡ����Ϊ1��ô���е����������ͬ�Ͻ���ת�ơ�

���Ӷ� $O(\log^2 n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define N 30
using namespace std;
int f[N+2][N+2][2];
int main()
{
	int n;
	scanf("%d",&n);
	f[N][0][1]=1;
	for(int i=N;i;i--)
		for(int j=0;j<=N;j++)
		{
			f[i-1][j][0]=(f[i-1][j][0]+f[i][j][0]*(1ll<<j))%mod;
			f[i-1][j+1][0]=(f[i-1][j+1][0]+f[i][j][0])%mod;
			if((n>>(i-1))&1)
			{
				f[i-1][j][0]=(f[i-1][j][0]+(j?1ll<<(j-1):1ll)*f[i][j][1])%mod;
				f[i-1][j][1]=(f[i-1][j][1]+(j?1ll<<(j-1):0)*f[i][j][1])%mod;
				f[i-1][j+1][1]=(f[i-1][j+1][1]+f[i][j][1])%mod;
			}
			else f[i-1][j][1]=(f[i-1][j][1]+(j?1ll<<(j-1):1ll)*f[i][j][1])%mod;
		}
	int ans=0;
	for(int i=0;i<=N;i++) ans=(1ll*ans+f[0][i][0]+f[0][i][1])%mod;
	printf("%d",ans);
	return 0;
}
```
