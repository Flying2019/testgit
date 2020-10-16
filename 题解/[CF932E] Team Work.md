### [链接](https://www.luogu.com.cn/problem/CF932E)
### 题目大意
求$\sum_{i=1}^n C(n,i)*i^k$
### 题解
考虑推式子。$i^k$ 与组合数不怎么匹配，考虑用第二类stirling公式，即 $a^k=\sum_{i=0}^{a}\begin{Bmatrix}k\\ i\end{Bmatrix}\times i!\times \binom{n}{i}$。

经过一系列化简式子可以得到 
$$\text{原式}=\sum_{i=0}^{n}\begin{Bmatrix}k\\ i\end{Bmatrix}\times n^{\underline{i}}\ 2^{n-i}$$

由于 $k$ 很小，直接 $n^2$ 处理第二类stirling数和后面的式子即可。复杂度 $O(k^2)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 5010
#define mod 1000000007
int s2[N][N];
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
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    s2[0][0]=1;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=i;j++)
        s2[i][j]=(s2[i-1][j-1]+1ll*s2[i-1][j]*j%mod)%mod;
    int ans=0,i2=ksm(2),r=ksm(2,n),r1=1;
    for(int i=0;i<=k;i++) ans=(ans+1ll*s2[k][i]*r1%mod*r%mod)%mod,r=1ll*r*i2%mod,r1=1ll*r1*(n-i)%mod;
    printf("%d\n",ans-(!k));
    return 0;
}
```
