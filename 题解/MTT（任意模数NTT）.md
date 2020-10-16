### [ģ����](https://www.luogu.com.cn/problem/P4245)
������̫���˲����ϵ��FFT��ֻ����ģNTT��

������˵������������NTTģ�� $m_1,m_2,m_3$ ȥ��ʾ���Ĵ𰸡�ͨ��Ϊ $998244353\ ,\ 1004535809\ ,\ 469762049$

���Է��֣�����ֻ��Ҫִ��3��NTT֮�����CRT�ϲ����ɡ�

�ر�ģ����� $m_1\times m_w\times m_3$ ���ܴܺ���Ҫ��__int128�����û��c++11����Ҫ�ر���

�����е�󣬵����ӶȻ��� $O(n\log n)$��
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define N 400010
#define ll int
using namespace std;
ll ksm(ll a,ll b,ll p)
{
    ll r=1;
    for(;b;b>>=1){if(b&1) r=1ll*r*a%p;a=1ll*a*a%p;}
    return r;
}
const ll mod1=998244353,mod2=1004535809,mod3=469762049,mod=1000000007,G=3;
int rev[N];
int get_rev(int n)
{
    int l=0,lim=1;
    while(lim<=n) l++,lim<<=1;
    for(int i=1;i<lim;i++)
    rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    return lim;
}
void ntt(ll f[],int lim,ll mod,int opt)
{
    for(int i=0;i<lim;i++)
    if(i<rev[i]) swap(f[i],f[rev[i]]);
    for(int mid=1;mid<lim;mid<<=1)
    {
        ll r=ksm(opt==1?G:ksm(G,mod-2,mod),(mod-1)/(mid*2),mod);
        for(int i=0;i<lim;i+=mid*2)
            for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
            {
                ll x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                f[i+j]=(x+y)%mod;
                f[i+j+mid]=(x-y+mod)%mod;
            }
    }
    if(opt==-1)
    {
        ll r=ksm(lim,mod-2,mod);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
    }
}
ll sf[N],sg[N];
void solve(ll f[],ll g[],ll h[],int lim,ll mod)//h=f*g
{
    for(int i=0;i<=lim;i++) sf[i]=f[i],sg[i]=g[i];
    ntt(sf,lim,mod,1);
    ntt(sg,lim,mod,1);
    for(int i=0;i<lim;i++) h[i]=1ll*sf[i]*sg[i]%mod;
    ntt(h,lim,mod,-1);
}
ll f[N],g[N],ans[3][N];
#define lll __int128
ll get(lll a,lll b,lll c)
{
    ll A=mod1,B=mod2,C=mod3;
	lll ans=0,m1=(lll)A*B*C;
	ans+=(lll)a*C%m1*B%m1*ksm(B,A-2,A)%m1*ksm(C,A-2,A)%m1;
	ans+=(lll)b*A%m1*C%m1*ksm(C,B-2,B)%m1*ksm(A,B-2,B)%m1;
	ans+=(lll)c*B%m1*A%m1*ksm(A,C-2,C)%m1*ksm(B,C-2,C)%m1;
	ans%=m1;
    return (ll)(ans%mod);
}
char str[N];
int main()
{
    scanf("%s",str+1);
    for(int i=0;i<n;i++) s[i+1]=(ss[i]=='a');
    return 0;
}
```
