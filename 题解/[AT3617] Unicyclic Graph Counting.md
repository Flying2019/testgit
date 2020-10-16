### [链接](https://www.luogu.com.cn/problem/AT3617)
### 题目大意
给定每个点的度数，求可行的基环树数量，$n\leq 300$。
### 题解
先考虑求树的数量怎么做。

考虑一种奇怪的编码：Prüfer编码。每次找到当前度数为一的节点中编号最小的点 $x$，加入与 $x$ 相邻的点，然后删掉 $x$，直到只剩下两个点。

可以证明，任何一颗有标号无根树都可以转换成一个Prüfer编码，同样**任意一个**Prüfer编码只代表唯一一颗有标号无根树。

显然，Prüfer编码中每个节点出现了它的入度 $-1$ 次。所以显然可以得出合法的树的数量就是合法的Prüfer编码数量。这个可以直接组合计数。

考虑基环树。首先我们假设单独枚举每个基环进行处理。我们考虑将环缩成一个点处理，并且这个点的编号是最大的。可以发现这种情况下可以直接套Prüfer编码。

接下来考虑每个结点在Prüfer编码中的出现次数。可以发现环上的点出现次数是入度 $-2$，特别的，环上与另外一个点相邻的那个点的出现次数是入度 $-3$。

再考虑统计答案。很显然可以推出，确定 $n$ 个点后不同的环的数量是 $\frac{(n-1)!}2$（一个环有旋转同构和翻转同构）。

可以发现环的数量只与环的大小有关。即

$$ans=\sum_{k}\left(\frac{(k-1)!(n-k-1)!}2\sum_{|S|=k}\sum_{u\in S}\prod_{i=1}^{n}{\frac{1}{(d[i]-1-2[\ i==u\ ]-[\ i\in S,i!=u\ ])!}}\right)$$

所以考虑枚举环的大小。用 $f_{i,j,0/1}$ 表示前 $i$ 个节点，环中有 $j$ 个点，没有/有点是环上与另外一个点相邻的点的权值之和（即 $sum_{k}$ 里面的东西）。

对于一个点分类讨论，然后dp即可。特别的，如果所有点构成一个环也算是基环树。需要特判这种情况。

复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 1000000007
#define N 510
using namespace std;
ll f[N][N][2],fac[N],inv[N];
ll ksm(ll a,ll b=mod-2)
{
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a%mod;
        a=a*a%mod;
    }
    return r;
}
int d[N];
int main()
{
    int n;
    scanf("%d",&n);
    if(n<=2){puts("0");return 0;}
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    f[0][0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=i;j++)
        {
            (f[i][j][0]+=f[i-1][j][0]*inv[d[i]-1])%=mod,(f[i][j][1]+=f[i-1][j][1]*inv[d[i]-1])%=mod;
            if(d[i]>=2 && j) (f[i][j][0]+=f[i-1][j-1][0]*inv[d[i]-2])%=mod,(f[i][j][1]+=f[i-1][j-1][1]*inv[d[i]-2])%=mod;
            if(d[i]>=3 && j) (f[i][j][1]+=f[i-1][j-1][0]*inv[d[i]-3])%=mod;
        }
    ll ans=0;
	for(int i=3;i<n;i++)
		ans=(ans+f[n][i][1]*fac[n-i-1]%mod*fac[i-1]%mod*inv[2]%mod)%mod;
    printf("%lld\n",(ans+f[n][n][0]*fac[n-1]%mod*inv[2])%mod);
    return 0;
}
```
