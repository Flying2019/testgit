### [����](https://atcoder.jp/contests/agc047/tasks/agc047_c)
### ��Ŀ����
�������� $a_i$���� $\sum_{i<j}{(a_i\times a_j\bmod p)}$��
### ���
��Ȼ��AGC������·���ˡ����� $F(x)=\sum{[a_i=x]}$����Ȼ�� $G(a)=\sum_{xy\bmod p=a}F(x)F(y)$����ô $\sum G(x)\times x$ ���Ǵ𰸡�

�˷��е���ģ�������·���� $\log_g a_i$ ���棬�� $F(x)=\sum{[g^{a_i}\bmod p=x]}$����Ȼ�� $G(a)=\sum_{(x+y)\bmod p=a}F(x)F(y)$����ô $\sum G(x)\times g^x$ ���Ǵ𰸡�

ֱ��FFT������ɣ�����������ʱҪ��ȥ $\sum a_i^2$ �ٳ���2��

���Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define N 400010
#define ll long long
#define mod 200003
#define G 11
using namespace std;
ll num[N],cnt[N],_11[N];
const double pi=acos(-1);
struct xu{
	double s,x;
	xu(double S=0.0,double X=0.0):s(S),x(X){};
	xu operator +(const xu a){return xu(s+a.s,x+a.x);}
	xu operator -(const xu a){return xu(s-a.s,x-a.x);}
	xu operator *(const xu a){return xu(s*a.s-x*a.x,s*a.x+x*a.s);}
};

void fft(xu a[],int n,int len,int opt)
{
	int rev[n];
	rev[0]=0;
	for(int i=1;i<n;i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
		if(rev[i]>i) swap(a[rev[i]],a[i]);
	}
	for(int i=1;i<n;i<<=1)
	{
		xu omg(cos(pi/i),opt*sin(pi/i));
		for(int j=0;j<n;j+=i*2)
		{
			xu orz(1,0);
			for(int k=0;k<i;k++)
			{
				xu n1=a[j+k],n2=orz*a[i+k+j];
				a[j+k]=n1+n2;
				a[i+j+k]=n1-n2;
				orz=orz*omg;
			}
		}
	}
	if(opt==1) return;
	for(int i=0;i<n;i++)
	{
		a[i].s=a[i].s/n;
		a[i].x=a[i].x/n;
	}
}
xu f[mod*4];
int main()
{
    int n;
    ll s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
    _11[0]=1;
    for(int i=1;i<=mod-2;i++)
    {
        _11[i]=1ll*_11[i-1]*G%mod;
        cnt[_11[i]]=i;
    }
    int m=1,l=0;
    while(m<=mod*2) m=m*2,l++;
    for(int i=1;i<=n;i++)
    if(num[i])f[cnt[num[i]]].s++;
    fft(f,m,l,1);
    for(int i=0;i<m;i++) f[i]=f[i]*f[i];
    fft(f,m,l,-1);
    // for(int i=0;i<m;i++)
    // if((ll)(f[i].s+0.5)) printf("%d:%d - %d\n",i,_11[i%mod],(ll)(f[i].s+0.5));
    ll ans=0;
    for(int i=0;i<mod*2;i++)
        ans+=1ll*_11[i%(mod-1)]*(ll)(f[i].s+0.5);
    for(int i=1;i<=n;i++) ans-=1ll*num[i]*num[i]%mod;
    ans/=2;
    printf("%lld\n",ans);
    return 0;
}
```
