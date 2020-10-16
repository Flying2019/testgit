### [����](http://115.236.49.52:83/contest/1523/problem/3)
���ȿ��Է��֣�����ÿ�� $l=a\times b\ ,\ gcd(a,b)=1$���� $len(l)=lcm(len(a),len(b))$��

�������ǲ������������� $m=p$ ���п��ǡ�

���Է��� $f_n=\left(\left(\sum_{i<n}{a^i\times c}\right)+x\times a^n\right)\bmod m$��

Ҳ��������Ҫ�ҵ���С�� $n$ ���� $\left(\sum_{i<n}{a^i\times c}\right)+x\times a^n \equiv x (\bmod m)$��

���������Ƿ��������ˡ����� $a\equiv 0(\bmod m)$�����ֱȽϺô�����Ȼ��ѭ����=1��

Ȼ�����ǾͿ��Լ�������ʽ�ӡ�
$$c\cdot\frac{a^n-1}{n-1}\equiv x(a^n-1)(\bmod m)$$
Ȼ���ٿ��ǣ������ $a\equiv 1(\bmod m)$ ����������� $m$ Ϊ��������Ȼ $n=1\text{ �� }m-1$

����ʣ����������ǿ��Է����� $n=m-1$ �����������Ⲣ����Ψһ�⡣���Է�������ж��� $n=a$ ������һ���� $n=ak$ ������

�������ǲ���ɸ������������С�����ӣ��� $m-1$ �����������ӽ����Գ�����ô������Ǵ𰸡�

���� $m=p^k$�����Է�����ѭ����Ҫô�� $m=p^{k-1}$ ��ȣ�Ҫô�ٳ��� $p$����֤һ�¼��ɡ�

�ر�ģ�����ĳЩ $m$ ���ѭ����Ϊ1��Ҫ���С�

���Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 5000010
#define int long long
#define ll long long
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
ll mod;
ll x;
struct F{
    int x,y;
    F(int X=0,int Y=0):x(X),y(Y){}
    F operator *(const F a){return F(1ll*x*a.x%mod,(1ll*x*a.y+y)%mod);}
};
ll nxt(F a){return 1ll*a.x*x+a.y;}
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1){if(b&1) r=1ll*r*a%mod;a=1ll*a*a%mod;}
    return r;
}
F operator ^(F a,int b)
{
    F r(1,0);
    for(;b;b>>=1){if(b&1) r=r*a;a=a*a;}
    return r;
}
void operator ^=(F &a,int b){a=a^b;}
int lcm(int a,int b){return a/gcd(a,b)*b;}
int pr[N],sp[N],tot;
bool p[N];
void pre(int n)
{
    p[1]=true;
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) pr[++tot]=i,sp[i]=i;
        for(int j=1;j<=tot && i*pr[j]<=n;j++)
        {
            p[i*pr[j]]=true;
            sp[i*pr[j]]=pr[j];
            if(i%pr[j]==0) break;
        }
    }
}
ll f[N];
signed main()
{
    int a,c,n;
    scanf("%lld%lld%lld%lld",&x,&a,&c,&n);
    F x0(a,c);
    pre(n);
    for(int i=1;i<=tot;i++)
    {
        mod=pr[i];
        while(mod*pr[i]<=n) mod*=pr[i];
        F x1(a%mod,c%mod);
        if(a%pr[i]==0) for(ll t=pr[i];t<=n;t*=pr[i]) f[t]=1;
        else if((a-1)%pr[i]==0)
        {
            ll l=0;
            if(nxt(x0)%pr[i]==x%pr[i]) l=1;
            else l=pr[i],x1^=pr[i];
            f[pr[i]]=l;
            for(ll t=1ll*pr[i]*pr[i];t<=n;t*=pr[i])
            {
                if(nxt(x1)%t!=x%t) l*=pr[i],x1^=pr[i];
                f[t]=l;
            }
        }
        else
        {
            ll l=pr[i]-1;
            for(ll u=l;u>1;u/=sp[u])
            if(ksm(a,l/sp[u])%pr[i]==1) l/=sp[u];
            f[pr[i]]=l;
            if(nxt(x0)%pr[i]==x%pr[i]) f[pr[i]]=1;
            x1^=l;
            for(ll t=1ll*pr[i]*pr[i];t<=n;t*=pr[i])
            {
                if(nxt(x1)%t!=x%t) l*=pr[i],x1^=pr[i];
                f[t]=l;
                if(nxt(x0)%t==x%t) f[t]=1;
            }
        }
    }
    ll ans=0;
    f[1]=1;
    for(int i=2;i<=n;i++)
    if(!f[i]){int x=i,y=1; for(;sp[x]==sp[i];x/=sp[i],y*=sp[i]);f[i]=lcm(f[x],f[y]);}
    for(int i=1;i<=n;i++) ans+=f[i];
    printf("%lld\n",ans);
    return 0;
}
```
