### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/D)
### 题目大意
构造3个01字符串A,B,C，定义 $f(a,b)$ 表示 $a,b$ 的最长公共子序列，满足 $f(A,B)=a,\ f(B,C)=b,\ f(A,C)=c$
### 题解
子序列有点麻烦，不妨考虑利用长度限制。

不妨假设 $a\leq b\leq c$

构造 $len(A)=c,\ len(B)=b,\ len(C)$ 不作限制。我们让A,B是C的子序列。接下来只要 $f(A,B)=a$ 即可。

考虑最简单的方式就是A全是1，B前a个是1，后面都是0。显然C只需要5000个1+5000个0即可。
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
