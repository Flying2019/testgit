### [����](http://codeforces.com/problemset/problem/538/F)
��С���µ�һ���⡣

���ȿ��Է��֣�һ�����Ӧ�ĸ���������ʵ���ࡣ������˵���� $u$ �� $k$ �����ж�Ӧ�ĵ��� $\lfloor\frac {n-2} k\rfloor+1$��

��ô����ö�����Ŀ��и��ף����Է��ֶ�Ӧ�� $k$ ��һ�����䡣

������˵ֱ�����۷ֿ飬Ȼ���ִ����ɡ�

���Ӷ� $O(n\sqrt n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int v[N];
int ans[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=2;i<=n;i++)
	{
		int l=1,r=0;
		const int m=i-2;
		for(;l<=m;l=r+1)
		{
			r=m/(m/l);
			if(v[m/l+1]>v[i]) ans[l]++,ans[r+1]--;
		}
		if(v[1]>v[i]) ans[l]++;
	}
	for(int i=1;i<n;i++) ans[i]+=ans[i-1],printf("%d ",ans[i]);
	return 0;
}
```
