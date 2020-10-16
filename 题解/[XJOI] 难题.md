### [����](http://115.236.49.52:83/contest/1561/problem/2)
����ö��������µ������ɫ��Ҫ�����������¸��������������

ע������һ���������������� $ans=\sum_{i=1}^{n}{E(\text{����}\ |\ \text{������µ���i��ɫ����})}$

�� $f_i$ ��ʾ�� $i$ �ָ���ɫ���򣬿����г����� $f_i=p\times{(f_{i-1}+f_{i+1})}+(1-2p)\times{f_i}+w\ ,\ f_s=0$��$w$ �����������ס�

���Է�����������һ����������������Ӧ�ü�������� $f_0$ �ĸ��ʡ����Է��� $f_i$ ��� $f_{i+1}$ �ĸ��ʺͱ�� $f_{i-1}$ �ĸ�����ͬ���׵ô�ʱ $f_i$ �� $f_s$ �ĸ���Ϊ $\frac{i}{s}$��

Ҳ���Ƕ��� $f_i$ ��˵�����������ֻ�� $\frac{i}{s}$ �Ĳ��ֶԴ�**�й���**������ $w=\frac{i}{s}$��

���������� $f_0=0,f_n=0$����Ϊ�����κι��ף����ɵ� $f_1=\frac{(s-1)^2}{s}$��Ȼ����Ƶó�����ʽ�Ӽ��ɡ�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 1000000007
#define ll long long
using namespace std;
ll f[N];
int a[N];
ll ksm(ll a,ll b=mod-2)
{
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a%mod;
        a=a*a%mod;
    }
    return r;
}
int main()
{
    int n,m=0;
    ll s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i],m=max(m,a[i]);
    f[0]=0,f[1]=1ll*(s-1)*(s-1)%mod*ksm(s)%mod;
    f[2]=2*f[1]-1;
    for(int i=1;i<m;i++)
    f[i+1]=(2*f[i]-f[i-1]-1ll*(s-1)*ksm(s-i)%mod+mod)%mod;
    ll ans=0;
    for(int i=1;i<=n;i++) ans=(ans+f[a[i]]+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}
```
