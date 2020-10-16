### [����](https://codeforces.com/contest/632/problem/E)
������һ���������ö���ʽ�����ݸ㣬�������ڳ���̫����ʱ�޿���5s��

����ñ����пɳ�֮���ˡ�

��Ȼ $O(n^4)$ �ı�����Ȼ���ܲ���ȥ�ġ�����ת�����⣬���ǲ�������С͵�õ�ȫ������С��ֵ����Ʒ��Ȼ�����ǰ�������Ʒ��ֵ��ȥ���������

��ô��Ŀ�ͱ���ˣ������ $k$ ����Ʒ���ʿ��ܵļ�ֵ��

��ת�����⣬���������м�ֵ����������Ҫ������Ʒ������ϡ�

������Ǻ����Եı����ˡ�ֱ��dp���ɡ�

���Ӷ� $O(n^3)$���ܵ÷ɿ졣
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
#define M 1010
using namespace std;
int a[M],d[M],f[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) d[i]=a[i]-a[1];
	memset(f,60,sizeof(f));
	f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=d[i];j<=N-10;j++) f[j]=min(f[j],f[j-d[i]]+1);
    for(int i=0;i<=N-10;i++)
        if(f[i]<=m) printf("%d ",m*a[1]+i);
	return 0;
}
```
