### [����](https://www.luogu.com.cn/jump/atcoder/5200)
������ʽ�ӡ���Ȼ���ǿ�������� $\displaystyle\sum_{i=1}^{n}\sum_{j=1}^{n}\operatorname{lcm}(a_i,a_j)$��Ȼ���ȥ $i= j$ ��/2���ɡ�

lcm��û��ʲô�����ʣ�����gcd���� $\displaystyle\sum_{i=1}^{n}\sum_{j=1}^{n}\frac{a_ia_j}{\operatorname{gcd}(a_i,a_j)}$��

������·ö�� $d=\operatorname{gcd}(i,j)$���� $\displaystyle\sum_d\sum_{i=1}^{ n}\sum_{j=1}^{n}[\operatorname{gcd}(a_i,a_j)=d]$��

���ǿ��Ǽ� $c_i=\sum_j[a_j=i]\ ,\ m=\max\{a_i\}$����ô���� $\operatorname{gcd}$ ����·���� $d$ �������� $\displaystyle\sum_{d=1}^{m}d\sum_{i=1}^{\lfloor\frac m d\rfloor}\sum_{j=1}^{\lfloor\frac m d\rfloor}[(i,j)=1]i\cdot j\cdot c_ic_j$��

����֪�� $\sum_{i|n}{\mu(i)}=[n==1]$�����Կ��Ի��� $\displaystyle\sum_{d=1}^{m}d\sum_{i=1}^{\lfloor\frac m d\rfloor}\sum_{j=1}^{\lfloor\frac m d\rfloor}\sum_{k|\operatorname{gcd}(i,j)}\mu(k)i\cdot j\cdot c_ic_j$��

���ǽ������˳�򣬼�

$$\sum_{d=1}^{m}d\sum_{k=1}^{\lfloor\frac m d\rfloor}\mu(k)k^2\sum_{i=1}^{\lfloor\frac m {dk}\rfloor}\sum_{j=1}^{\lfloor\frac m {dk}\rfloor}i\cdot j\cdot c_{idk}c_{jdk}$$

��Ϊö�� $dk$����

$$\sum_{d=1}^{m}d\sum_{k|d}\mu(k)k\sum_{i=1}^{\lfloor\frac m {d}\rfloor}\sum_{j=1}^{\lfloor\frac m {d}\rfloor}i\cdot j\cdot c_{id}c_{jd}$$

$$=\sum_{d=1}^{m}d\sum_{k|d}\mu(k)k\left(\sum_{i=1}^{\lfloor\frac m {d}\rfloor}i\cdot c_{id}\right)^2$$

$$=\sum_{d=1}^{m}d\sum_{k|d}\mu(k)k\left(\sum_{d|i}i\cdot c_{i}\right)^2$$

��Ȼǰ���Ǹ���������ǰ׺�ͣ������Ǹ����Ǻ�׺�͡�Ī����˹��ֱ��ɸ�ͺ��ˡ�

ö����������ʱ�临�Ӷ� $O(n\ln n)$��
```cpp#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 998244353
#define inv2 ((mod+1)/2)
using namespace std;
int mu[N],pr[N],tot;
int f[N],g[N],cnt[N];
bool p[N];
void pre(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) pr[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot && i*pr[j]<=n;j++)
        {
            p[i*pr[j]]=1;
            if(i%pr[j]==0){mu[i*pr[j]]=0;break;}
            mu[i*pr[j]]=mod-mu[i];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;1ll*i*j<=n;j++)
        f[i*j]=(f[i*j]+1ll*i*mu[i]+mod)%mod;
    }
}
int inv[N];

int main()
{
    int n,m=0;
    int res=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        res=(res-a+mod)%mod;
        cnt[a]++;
        m=max(m,a);
    }
    inv[1]=1;
    for(int i=2;i<=m;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    pre(m);
    for(int i=1;i<=m;i++)
    {
        int t=0;
        for(int j=1;1ll*i*j<=m;j++)
            t=(t+1ll*cnt[i*j]*j%mod)%mod;
        res=(res+1ll*f[i]*i%mod*t%mod*t%mod)%mod;
    }
        
    printf("%d\n",1ll*res*inv2%mod);
    return 0;
}
```
