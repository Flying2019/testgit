### [����](https://codeforces.com/problemset/problem/582/C)
��������ж�һ���Ӵ��Ƿ�����������

�����������ҳ�����֮��� $g=\gcd$����Ȼ������ $a_i\equiv a_{l+j}\pmod g$ ����Ҫ�� $a_{l+j}\geq a_i$��

Ҳ����˵�����ǰ� $\gcd$ ��ͬ�Ŀ���һ�飬��ô��ͬ����ֻ�����ֵ�����Ӵ��г��֡�

��ô������·������ö�� $\gcd$������һ�����ֵ����Ӳ����� $O(\sqrt n)$������������ȫ���С�

Ȼ���ǽ���ͬ�Ŀ���һ�飬�����ڵ����ֵ���������ܻ���ֶ�����ֵ����ô��Ȼ��Щ�����Լ�¼�𰸡�

�������ͳ�ơ����Է���������ǰѿ��Լ�¼�𰸵Ĳ��ֱ�1�����ܵı�0����ô���ǿ��Դ���һ��ǰ׺�͡�������Ҫע�������0Ӧ��ֱ����0�����Ǽ̳���һλ�Ľ����

���������Ǿʹ������ $i$ �������Դ������󳤶ȡ�Ȼ�������ټ�¼һ������ $g$ ��ʾ����Ϊ��� $i$ �Ĺ̶��Ҷ˵�����й����Ƕ��١���Ȼ���� $[i=g]$ ��һ��ǰ׺�ͼ��ɡ�

���Ӷ� $O(n\sqrt n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 400010
#define ll long long
using namespace std;
int a[N],f[N],g[N],h[N],c[N];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) g[i]=gcd(i,n);
	ll ans=0;
	for(int d=1;d<n;d++)
	if(n%d==0)
	{
		for(int i=1;i<=n;i++) c[i]=c[i-1]+(g[i]==d);
		for(int i=0;i<d;i++) f[i]=0;
		for(int i=0;i<n;i++) f[i%d]=max(f[i%d],a[i]);
		for(int i=0;i<n;i++) h[i]=h[i+n]=f[i%d]==a[i];
		for(int i=n*2-2;i>=0;i--)
			if(h[i]) h[i]+=h[i+1];
		for(int i=0;i<n;i++) ans+=c[min(n-1,h[i])];
	}
	printf("%lld\n",ans);
	return 0;
}
```
