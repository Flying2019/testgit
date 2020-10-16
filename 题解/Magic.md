### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/E)
### 题目大意
给定 $n$ 个串，可以任意交换字符串的位置。询问有多少种顺序,最后组合的字符串的不同子序列个数为偶数。
### 题解
考虑一个串的不同子序列个数怎么算。

令 $f_{i,j}$ 表示前 $i$ 个字符组成的字符串中以 $j$ 结尾的不同子序列个数，$\text{sum}$ 表示当前答案。

考虑如果 $s_i=x$，可以推出 $f_{i,j}=f_{i-1,j}+sum_{i-1},\ sum_i=sum_{i-1}*2-f_{i-1,j}$。即，对于所有本质不同的字符串，后面加上一个字符也还是本质不同的。

由于询问的是奇偶性，所以考虑 $\mod 2$。可以发现 $f_{i,j}=f_{i-1,j}+[\ j=x\ ]sum_{i-1},\ sum_i=f_{i-1,j}$。本质是将 $f_x$ 项和 $sum$ 交换。

又可以发现初始 $f_{i,j}=0,\ sum_0=1$。可以发现一个 $f$ 中只有一位为1。所以显然可以dp。

不妨设 $f_{s,j}$  表示使用 $s$ 集合内的字符串，处理完后1的位置在 $j$ 的方案数。这里认为 $f_{s,0}$ 表示 $sum$。

显然可的状压dp方程。简单转移即可。复杂度 $O(2^n*26*n)$。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 200010
#define M 1<<21
#define C 28
using namespace std;
char str[N];
ll f[M][C];
int swp[25][C];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",str+1);
        int s=strlen(str+1);
        for(int j=0;j<=26;j++)
        {
            swp[i][j]=j;
            for(int k=1;k<=s;k++)
            if(swp[i][j] && str[k]-'a'+1==swp[i][j]) swp[i][j]=0;
            else if(!swp[i][j]) swp[i][j]=str[k]-'a'+1;
        }
    }
    f[0][0]=1;
    for(int i=0;i<1<<n;i++)
        for(int j=0;j<=26;j++)
        if(f[i][j])
        {
            for(int k=0;k<n;k++)
            if(!(i&(1<<k)))
            {
                int v=i|(1<<k);
                f[v][swp[k][j]]+=f[i][j];
            }
        }
    ll ans=0;
    for(int i=1;i<=26;i++) ans+=f[(1<<n)-1][i];
    printf("%lld\n",ans);
    return 0;
}
```
