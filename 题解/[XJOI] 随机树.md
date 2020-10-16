### [链接](http://115.236.49.52:83/contest/1583/problem/1)
考虑期望的定义。令 $f_n$ 表示 $n$ 个点的所有方案的总和，那么答案 $g_n=\frac{f_n}{(n-1)!}$。

考虑求 $f_n$。根据定义，$f_n$ 是所有方案的所有点的入度的平方和，即：

$$f_n=\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{deg_i^2}$$

考虑转移，即考虑新加入一个点，那么这个点可以向前连边，不妨枚举 $fa$，即：

$$f_{n+1}=\sum_{u=0}^{n-1}\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{\left(deg_i+[i=u]\right)^2}$$

暴力拆开可得：

$$f_{n+1}=nf_n+2\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{deg_i}+n\sum_{deg\text{ is possible}}1$$

根据树的性质，显然有：

$$\sum_{deg\text{ is possible}}1=(n-1)!$$

$$\sum_{i=0}^{n-1}{deg_i}=2(n-1)$$

代入原式可得：

$$f_{n+1}=nf_n+4(n-1)(n-1)!+2\times n!$$

对于 $g_n$ 有

$$g_{n+1}=\frac{f_{n+1}}{n!}$$

$$=\frac{nf_n+4(n-1)(n-1)!+2\times n!}{n!}$$

$$=\frac{f_n}{(n-1)!}-\frac{4}{n}+6$$

$$=g_n-\frac{4}{n}+6$$

所以显然可得最终答案。

时间复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define ll long long
#define db double
using namespace std;
db g[N];
int main()
{
    int n;
    scanf("%d",&n);
    if(n>=N-10)
    {
        double ans=2*n-2+4*(n-2);
        for(int i=2;i<=n-1;i++)
        ans-=4.0/i;
        printf("%.6lf\n",ans);
        return 0;
    }
    g[1]=0;
    g[2]=2;
    for(int i=2;i<n;i++)
    g[i+1]=g[i]+4.0*(i-1)/i+2.0;
    printf("%.6lf",g[n]);
    return 0;
}
```
