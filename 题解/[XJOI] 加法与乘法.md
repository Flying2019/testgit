### [链接](http://115.236.49.52:83/contest/1588/problem/2)
毒瘤特判题。。。

首先不考虑一些奇奇怪怪的东西，可以发现本质上有 $\displaystyle s\times b^n+a\sum_{i=0}^{n}k_ib^i=t$。

可以发现显然 $\forall\ i<n\ ,\ k_i<b$，这就是一个 $b$ 进制数。

不妨枚举 $n$，贪心处理 $k_i$ 即可。复杂度 $O(\log^2 n)$。

但是这题有一堆特判，包括但不限于 $b=0,a=0,t<s,\cdots$。

特别的，这题数据范围 $10^{18}$，由于2e18超过了double 的精度，用1e18做inf会被卡。。。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 100010
using namespace std;
int main()
{
    ll s,t,a,b;
    scanf("%lld%lld%lld%lld",&s,&t,&a,&b);
    if(s==t){puts("0");return 0;}
    if(t<s)
    {
        if(b!=0){puts("-1");return 0;}
        if(t==0 && b==0){puts("1");return 0;}
        if(a==0 || t%a){puts("-1");return 0;}
        printf("%lld\n",t/a+1);
        return 0;
    }
    if(b==0)
    {
        if(!a){puts("-1");return 0;}
        ll r1=((t-s)%a==0)?(t-1):(long long)(2e18);
        ll r2=(t%a)?2e18:t/a+1;
        // if(r1>r2) r1=r2;
        printf("%lld\n",r1>=2e18?-1:r1);
        return 0;
    }
    if(b==1){if(a==0) puts("-1");else printf("%lld\n",(t-s)%a?-1:(t-s)/a);return 0;}
    if(a==0){int cnt=0;for(;s<t && t%b==0;t=t/b,cnt++);printf("%d\n",s==t?cnt:-1);return 0;}
    if(a==1 && s)
    {
        ll ans=0;
        ll u=t;
        for(;s<=u/b;u=u/b) ans+=u%b+1;
        ans+=u-s;
        printf("%lld\n",ans);
        return 0;
    }
    if(s>t/b){if(a==0) puts("-1");else printf("%lld\n",(t-s)%a?-1:(t-s)/a);return 0;}
    ll k=0;
    if(s==0) k++,s+=a;
    ll ans=2e18;
    for(ll m=0;;m++,s*=b)
    {
        ll t1=t-s;
        if(t1<0) break;
        if(t1%a) continue;
        t1/=a;
        ll r=m;
        for(int i=m;i>=1;i--)
        {
            r+=t1%b;
            t1/=b;
        }
        r+=t1;
        ans=min(ans,r);
    }
    printf("%lld\n",ans+k>=2e18?-1:ans+k);
    return 0;
}
```
