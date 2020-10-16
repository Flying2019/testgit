### [����](https://codeforces.com/contest/850/problem/F)
����ö��������µ������ɫ��Ҫ�����������¸��������������

ע������һ���������������� $ans=\sum_{i=1}^{n}{E(\text{����}\ |\ \text{������µ���i��ɫ����})}$

�� $f_i$ ��ʾ�� $i$ �ָ���ɫ���򣬿����г����� $f_i=p\times{(f_{i-1}+f_{i+1})}+(1-2p)\times{f_i}+w\ ,\ f_s=0$��$w$ �����������ס�

���Է�����������һ����������������Ӧ�ü�������� $f_0$ �ĸ��ʡ����Է��� $f_i$ ��� $f_{i+1}$ �ĸ��ʺͱ�� $f_{i-1}$ �ĸ�����ͬ���׵ô�ʱ $f_i$ �� $f_s$ �ĸ���Ϊ $\frac{i}{s}$��

Ҳ���Ƕ��� $f_i$ ��˵�����������ֻ�� $\frac{i}{s}$ �Ĳ��ֶԴ�**�й���**������ $w=\frac{i}{s}$��

���������� $f_0=0$����Ϊ�����κι��ף����ɵ� $f_1=\frac{(s-1)^2}{s}$��Ȼ����Ƶó�����ʽ�Ӽ��ɡ�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 1000000007
#define N 100010
using namespace std;
int ksm(ll a,int b=mod-2)
{
	ll ans=1;
	for(;b;b>>=1)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
int a[N],f[N];
ll sum;
int main()
{
	int n,maxn=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i],maxn=max(maxn,a[i]);
	int inv=ksm(sum);
	f[1]=1ll*(sum-1)*(sum-1)%mod*inv%mod;
	f[2]=(f[1]*2-1+mod)%mod;
	for(int i=1;i<=maxn;i++)
	f[i+1]=((2*f[i]%mod-f[i-1]+mod)%mod-1ll*(sum-1)*ksm(sum-i+mod)%mod+mod)%mod;
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+f[a[i]])%mod;
	printf("%d\n",ans);
	return 0;
}
```
