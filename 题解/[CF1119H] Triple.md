### [����](http://codeforces.com/contest/1119/problem/H)
���������������� $f[i][a_i]=x,f[i][b_i]=y,f[i][c_i]=z$��FWT�����

������ $F_i=\text{FWT}(f_i)$��$G(x)=\prod F_i(x)$�����Է��� $\text{IFWT}(G)$ ���Ǵ𰸡����Ӷ� $O(n\times 2^k)$��ֱ�ӱ�ը��

������·�����ǲ������������� $\displaystyle\bigotimes_{i\in[1,n]}{a_i}$������ڴ�������ȥ�ͺ��ˡ��������е� $a_i$ �������0��

˼����� $F_i(x)$ ��ʲô���ʡ�

���Է��֣�ÿ�� $f_i(x)$ ֻ������λ�ò���0������ö��������λ���ھ����Ľ����

����� $\text{count}(i)$ ��ʾi�Ķ�������1�ĸ��������Է��� $F_i(x)=(-1)^{\text{count}(x\&a_i)}x+(-1)^{\text{count}(x\&b_i)}y+(-1)^{\text{count}(x\&c_i)}z$��

���� $a_i=0$������ $F_i(t)=x+(-1)^{\text{count}(t\&b_i)}y+(-1)^{\text{count}(t\&c_i)}z$��$G(t)=\prod{x+(-1)^{\text{count}(t\&b_i)}y+(-1)^{\text{count}(t\&c_i)}z}$��

���Է��֣��������ÿ�� $t$ ���Ǵ���� $x+y+z,\ x+y-z,\ x-y+z,\ x-y-z$ ������ķ����� $c_1,\ c_2,\ c_3,\ c_4$����ô $G(t)=(x+y+z)^{c_1}+(x+y-z)^{c_2}+(x-y+z)^{c_3}+(x-y-z)^{c_4}$��

���������� $c_1,c_2,c_3,c_4$�������� x=0,y=1,z=0�����Է����ж���ĳ�� $t$ �� $\sum{F_i(t)}=c_1+c_2-c_3-c_4$����Ϊֻ��yΪ1����ô $c_1$ ���� $x+y+z$ �� $y$ ��ϵ������ $c_1$ �Ĺ��ס�

Ȼ����ݷ������� $\sum{F_i(t)}=\text{FWT}(\sum f_i(t))$��

ͬ���������� x=0,y=0,z=1���� $\text{FWT}(\sum{f_i(t)})=c_1-c_2+c_3-c_4$��

�� x=0,y=0,z=1���� $\text{FWT}(\sum{f_i(t)})=c_1-c_2+c_3-c_4$��

��Ȼ���� $c_1+c_2+c_3+c_4=n$

�ۺ���4��ʽ�ӣ��Ϳ����Ƴ� $c_1,c_2,c_3,c_4$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define M 1<<17
#define mod 998244353
#define inv2 (mod+1)/2
using namespace std;
#define ll long long
int n,m;
void fwt(ll f[],int opt)
{
    for(int i=1;i<m;i<<=1)
        for(int j=0;j<m;j+=i<<1)
            for(int k=j;k<j+i;k++)
            {
                int x=f[k],y=f[i+k];
                f[k]=x+y;
                f[i+k]=x-y;
                if(opt==-1) f[k]=1ll*f[k]*inv2%mod,f[i+k]=1ll*f[i+k]*inv2%mod;
            }
}
ll f[M],f1[M],f2[M],f3[M];
ll ksm(ll a,ll b=mod-2)
{
    a=(a%mod+mod)%mod;
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int main()
{
    ll x,y,z,all=0;
    scanf("%d%d%lld%lld%lld",&n,&m,&x,&y,&z);
    m=1<<m;
    for(int i=1;i<=n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        all^=a;
        f1[a^b]++; f2[a^c]++; f3[b^c]++;
    }
    fwt(f1,1),fwt(f2,1),fwt(f3,1);
    for(int i=0;i<m;i++)
    {
        ll c1=(n+f1[i]+f2[i]+f3[i])/4;
        ll c2=(n+f1[i])/2-c1,c3=(n+f2[i])/2-c1,c4=(n+f3[i])/2-c1;
        f[i]=1ll*ksm(x+y+z,c1)*ksm(x+y-z,c2)%mod*ksm(x-y+z,c3)%mod*ksm(x-y-z,c4)%mod;
    }
    fwt(f,-1);
    for(int i=0;i<m;i++)
    printf("%lld ",(f[i^all]%mod+mod)%mod);
    return 0;
}
```
