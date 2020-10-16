### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/F)
### ��Ŀ����
����һ�����У����� $\forall 1\leq j\leq i\leq n-j$���� $2\times a_{i}\neq a_{i-j}+a_{i+j}$��
### ���
���� $a_i=i$������Ȼ�����ǲ����������ģ���������Ҫ������

��ô�죿ֱ�ӽ���ż���飬������ǰ��ż���ź��档

�����ԣ�������ô�����Ҵ��ң���������һ�� $i-j< \frac n 2 < i+j$ Υ��������������Ϊ���� $a_{i-j}+a_{i+j}$ ��ȻΪ��������Ȼ������������

ͬ�����������䰴������ʽ�ݹ鴦���õ�������Ҳ�����ܴ���һ������м�� $i-j,i+j$ Υ��������

������ȷ����Ȼ�����Ӷ� $O(n\log n)$������Ȼ���ֺ�FFT��rev�������һ�ޣ���
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 50010
using namespace std;
int num[N],swp[N];
void work(int a[],int n)
{
	if(n==1) return;
	int v=(n+1)>>1;
	if(n&1)
	{
		for(int i=0;i<v;i++) swp[i]=a[i*2];
		for(int i=0;i<v-1;i++) swp[i+v]=a[i*2+1];
		for(int i=0;i<n;i++) a[i]=swp[i];
		work(a,v);
		work(a+v,v-1);
	}
	else
	{
		for(int i=0;i<v;i++) swp[i]=a[i*2];
		for(int i=0;i<v;i++) swp[i+v]=a[i*2+1];
		for(int i=0;i<n;i++) a[i]=swp[i];
		work(a,v);
		work(a+v,v);
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) num[i]=i+1;
	work(num,n);
	for(int i=0;i<n;i++) printf("%d ",num[i]);
	return 0;
}
```
