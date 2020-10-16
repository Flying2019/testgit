### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102647/problem/A)
### ��Ŀ����
����һ������Ϊ $m(n\leq 4\times 10^6)$ ������ $a_i\leq 20000$��ѯ�� $m(m\leq 2\times 10^5)$ �Σ�ÿ��һ���� $b_i\leq 20000$�����������ж��ٸ������������� $\gcd$ ���Ϊ $b_i$��
### ���
���ȿ��Է���һ�����ʣ�һ�����ֵ����������� $O(\log n)$ ����ġ�

����һ��������������ÿ�β���һ�������������������ĳ��ָ���������ǰһ�������п��ܳ��ֵ� $\gcd$ ���д���ͳ��ÿ�� $\gcd$ �ĳ��ִ�����

���������Ǹ����ʣ�ǰһ�������п��ܳ��ֵ� $\gcd$ Ҳ�� $O(\log n)$ ���𣬿������ⷢ�������Ĵ�������� $O(\log n)$ �ġ�

�������һ��map����ͨ�������Ӷ� $O(n\log^2 a)$�����ǽ�ܿ���Ϊ�󲿷����ֵ�����������ʵֻ�и�λ������
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#define N 4000010
#define ll long long
#define mi map<int,ll>
using namespace std;
int a[N];
mi ans,u,pre;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		u.swap(pre);
		u.clear();
		scanf("%d",&a[i]);
		u[a[i]]++;
		for(auto t:pre) u[__gcd(a[i],t.first)]+=t.second;
		for(auto t:u) ans[t.first]+=t.second;
	}
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int x;
		scanf("%d", &x);
		printf("%lld\n", ans[x]);
	}
	return 0;
}
```
