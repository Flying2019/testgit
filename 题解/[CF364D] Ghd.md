### [����](https://codeforces.com/contest/364/problem/D)
### ��Ŀ����
����һ������Ϊ $n$ �����У��ʴ���ѡ�� $\frac n 2$ �����֣����� $\text{gcd}$ �Ƕ��١�
### ���
���ȿ���һ��̰�ģ������ն�һ������ $x$���������������ѡ�ļ����С�

Ȼ�������ҳ������������� $p_i$����һ����Ȼ���¼һ������ $c_j$�������������� $a_i$�����Ƕ��ֳ� $\operatorname{gcd}(a_i,x)$ ��λ�� $p$���� $c_p$ ��1��

Ȼ��������һ������ǰ׺�ͣ��� $c_i\leftarrow\sum_{j=i+1}^{t}[p_i|p_j]c_j+c_i$��

�����Զ�������������һ�� $c_i\geq \frac n 2$ �� $p_i$ ���Ǵ𰸡�

����������ǰ���� $x$ �������ѡ�ļ����С������������ֻ�� $\frac 1 2$�����Զ�ö�ټ��ξͺ��ˡ�

���Ӷ� $O(Tn\log n+T\sqrt a)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
ll a[N];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll pr[N],t;
int cnt[N];
int main()
{
	int n;
	scanf("%d",&n);
	srand(n*2);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ll ans=0;
	for(int _=0;_<=10;_++)
	{
		memset(cnt,0,sizeof(cnt));
		ll x=a[1ll*rand()*rand()%n+1];
		t=0;
		for(int i=1;1ll*i*i<=x;i++)
		if(x%i==0){pr[++t]=i;if(1ll*i*i!=x) pr[++t]=x/i;}
		sort(pr+1,pr+t+1);
		for(int i=1;i<=n;i++)
			cnt[lower_bound(pr+1,pr+t+1,gcd(x,a[i]))-pr]++;
		for(int i=1;i<=t;i++)
			for(int j=i+1;j<=t;j++)
			if(pr[j]%pr[i]==0) cnt[i]+=cnt[j];
		for(int i=t;i;i--)
		if(2*cnt[i]>=n) ans=max(ans,pr[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```
