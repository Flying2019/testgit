### [����](https://codeforces.com/problemset/problem/1198/F)
������˼��һ���⡣

�����������ֽ⣬���Է���ÿ���������ֻ��9�������ӡ�Ҳ����˵����Ҫ���������ֳַ��������ϣ�ÿ�����϶���ÿ��������������һ������û�и������ӡ�

������δ�����Ȼ����һ�������̰�ģ�����ĳ�����ּ���1�����ܼ�Сgcd����ô�ͼ���1������ͼ���2�����������2������ȥ��

���ǿ�������̰��ʲôʱ���Ǵ�ġ���ĳ�����ּ���1�����У�������һ�����ּ���1��������ּ���2��

��������2��15���Ǳ��������1��ʵ����û���ô���

�����������Կ������ɹ�����ʵ���ߵġ���Ϊ�����Ĵ��������һ��������8����Ҳ��������Ҫ����������Բ�����8�ԡ�

��ô������ $\frac 1 {2^8}$ �����ܽ�����⡣��ʵ����������������ĳЩ�ط������ظ��ģ��ɹ��ĸ�����ʵԶ�������ֵ��

�ظ�100�ξ��㹻�ˡ�ʱ�临�Ӷ� $O(100n\log a)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int num[N],id[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
bool _2[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]),id[i]=i;
	for(int _=0;_<100;_++)
	{
		random_shuffle(id+1,id+n+1);
		int g1=num[id[1]],g2=0;_2[id[1]]=false;
		for(int i=2;i<=n;i++)
		if(num[id[i]]%g1==0) g2=gcd(num[id[i]],g2),_2[id[i]]=true;
		else g1=gcd(g1,num[id[i]]),_2[id[i]]=false;
		if(g1==1 && g2==1){puts("YES");for(int i=1;i<=n;i++) printf("%d ",1+(int)_2[i]);return 0;}
	}
	puts("NO");
	return 0;
}
```
