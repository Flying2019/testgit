### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102661/problem/A)
### ��Ŀ����
���� $p(x)$ ��ʾ�� $x$ ��Fibonacci����

��
$$\sum_{\forall i\in[1,n],\ a_i\in [1,k]}p\left({\sum_{i=1}^{n}a_i}\right)$$
### ���
�������ǻ���ʽ�ӡ����� $g(x)=\text{����}{\sum_{i=1}^{n}a_i}=x,a_i\in [1,k]\ \text{��}a_i\text{����}$�����Է��ִ� $=\sum_x{p(x)\times g(x)}$

�Ⱥ���  $p$ �����ǹ��� $g$ ���ɺ��������Է�����
$$G(x)=x\times(\sum_{i=0}^{n-1}x^i)^k$$
������Fibonacci������
$$p(n)=\frac 1{\sqrt{5}}\left[\left(\frac{\sqrt{5}+1}2\right)^n-\left(\frac{1-\sqrt{5}}2\right)^n\right]$$
���Է����� $ans=\sum_n{p(n)\times [x^n]G(n)}$

��ʽ�ӿɵ�
$$ans=\frac 1{\sqrt{5}}\sum_n{\left[\left(\frac{\sqrt{5}+1}2\right)^n\times [x^n]G(x)-\left(\frac{1-\sqrt{5}}2\right)^n\times [x^n]G(x)\right]}$$
��Ȼ��Ϊ�� $\sum_{i<k} a^i[x^i]F(x)=F(a)-F(a^k)$��������
$$ans=\frac 1{\sqrt{5}}\left[G\left(\frac{\sqrt{5}+1}2\right)-G\left(\frac{1-\sqrt{5}}2\right)\right]$$
���Է��� $G(x)$ �ı����ǵȱ�������ͣ������ô������ɡ�
��
��
��
��
��
��
��
�ٵġ���������ϣ���ش���ʽ�ӣ����� $\sqrt{5}$ �� $10^9+7$ ��û�ж��塣��Ϊ5�� $10^9+7$ ��û�ж���ʣ�ࡣ

����ô�죿���ǿ���������������ֱ�Ӷ���һ�ֶ�Ԫ�� $(a,b)$������ $(a,b)+(c,d)=(a+c,b+d)$��$(a,b)\times(c,d)=(ac+5bd,ad+bc)$��

��Ȼ������Fibonacci�Ǹ��������������������Ķ�Ԫ���е� $b$ һ��Ϊ0��ֱ����� $a$ ���ɡ�

���Ӷ� $O(T\log n^2)$��
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define ll long long
#define mod 1000000007
#define inv2 (mod+1)/2
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
struct node{
    ll x,y;//x+y*sqrt(5)
    node(ll X=0,ll Y=0):x(X),y(Y){}
    node operator +(node a){return node((x+a.x)%mod,(y+a.y)%mod);}
    node operator -(node a){return node((x-a.x+mod)%mod,(y-a.y+mod)%mod);}
    node operator *(node a){return node((1ll*x*a.x+5ll*y*a.y)%mod,(1ll*x*a.y+1ll*y*a.x)%mod);}
};
node ksm(node a,ll b=mod-2)
{
    node r=node(1,0);
    for(;b;b>>=1)
    {
        if(b&1) r=r*a;
        a=a*a;
    }
    return r;
}
node get_sum(node a,ll b)
{
    if(b==0) return 0;
    if(b==1) return a;
    node q=get_sum(a,b>>1),r=ksm(a,b);
    if(b&1) return q*(ksm(a,b>>1)+1)+r;
    return q*(ksm(a,b>>1)+1);
}
const node x1=node(inv2,inv2),x2=node(inv2,mod-inv2);
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        ll n,k;
        scanf("%lld%lld",&n,&k);
        node x=ksm(get_sum(x1,n-1)+1,k)*x1;
        node y=ksm(get_sum(x2,n-1)+1,k)*x2;
        printf("%lld\n",((x-y).y+mod)%mod);
    }
    return 0;
}
```
