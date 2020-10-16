### [����](https://vjudge.net/problem/Aizu-2970/origin)
### ��Ŀ����
���������û� $A,B$������С�� $k$ ��ʹ $A\times B^k$ �Ľ�����������ֵ���������
### ���
���Է��֣����� $A$ ��ÿһ�����֣����� $k$ �ı仯��һ��ѭ���ڡ���������Ϊ $r_i$��

�ֿ��Է��֣�����ÿһλ $i$ ��ĳһ�� $k$ ������ $i$�����û�г��ֵ�Ȼ�����޽⣩�����������ʱ����С $k$ ֵΪ $t_i$��

���Է������� $n$ �����󣬶�һ���� $r_i\leq n$��������ȫ������ $O(n^2)$ ����ɲ�����

�����ԣ�����Ҫ���ҵ�һ����С�� $x\in\Bbb Z$��ʹ������ $\forall\ 1\leq i\leq n,\ x\equiv t_i\ (\bmod r_i)$��

����Ȼ����һ��excrt��ֱ����ģ��ͺ��ˡ�

���Ӷ� $O(n^2)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1100
#define ll long long
ll mul(ll a,ll b,ll mod)
{
    ll res=0;
    while(b)
    {
        if(b&1) res=(res+a)%mod;
        a=a*2%mod;
        b>>=1;
    }
    return res;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll g=exgcd(b,a%b,x,y);
    ll p=x;
    x=y;
    y=p-a/b*y;
    return g;
}
int xa[N],xb[N],n;
ll excrt()
{
    ll mod=xb[1],ans=xa[1];
    for(int i=2;i<=n;i++)
    {
        ll x,y;
        ll a=mod,b=xb[i],c=(xa[i]-ans%b+b)%b;
        ll g=exgcd(a,b,x,y);
        if(c%g!=0) return -1;
        x=mul(x,c/g,b/g);
        ans+=x*mod;
        mod*=b/g;
        ans=(ans%mod+mod)%mod;
    }
    return (ans%mod+mod)%mod;
}
int id[N],p1[N],p2[N];
bool vis[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p1[i]),id[p1[i]]=i;
    for(int i=1;i<=n;i++) scanf("%d",&p2[i]);
    memset(xa,-1,sizeof(xa));
    for(int rt=0;rt<=2*n;rt++)
    {
        for(int i=1;i<=n;i++)
        if(p1[i]==i)
        {
            if(xa[i]<0) xa[i]=rt;
            else if(!xb[i]) xb[i]=rt-xa[i];
        }
        for(int i=1;i<=n;i++) p1[i]=p2[p1[i]];
    }
    for(int i=1;i<=n;i++)
    if(!xb[i]){puts("-1");return 0;}
    printf("%lld\n",excrt());
    return 0;
}
```
