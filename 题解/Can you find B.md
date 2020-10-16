### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/F)
### 题目大意
给定一个长度为 $n\ (n\leq 100)$ 的数列 $a_i$，保证 $a_i\in\ [1,100]$，求一个完全互质的数列 $b_i$，使得 $\displaystyle\sum_{i=1}^{n}|b_i-a_i|$ 最小。
### 题解
考虑互质就是没有一个的质因子在两个以上数字中出现过。而且可以发现，如果一个数字 $>100$ 显然不会选，所以考虑用状压dp。

考虑1~100的质数有25个，直接dp显然会TLE。但是可以发现，1~50的质数只有15个。

考虑一个性质：假如一个质数大于50，显然它最多只会单独出现。显然，如果可以选择多个这样的质数，选最小的一定更优。

同时考虑如果有一个大于50的质数，需要一个 $a_i$ 去匹配，选最大的一定不会更差。

所以考虑先将 $a_i$ 排序，先用小于50的质数处理出前 $i$ 个数的结果。然后考虑贪心选择大于50的质数，处理出后 $j$ 个数和大于50的质数匹配的最小代价。简单处理即可。

复杂度 $O(n*a*2^{15})$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;
const int p[26]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97},o=14;
int num[N];
int f[N][1<<o],st[N];
void check(int n)
{
    memset(f,60,sizeof(f));
    f[0][0]=0;
    for(register int i=1;i<=n;i++)
        for(register int s=0;s<1<<o;s++)
        if(f[i-1][s]<=100000000)
        {
            f[i][s]=min(f[i][s],f[i-1][s]+num[i]-1);
            for(register int j=2;j<=100;j++)
            {
                if(st[j]==-1 || (s&st[j])) continue;
                int t=s|st[j];
                f[i][t]=min(f[i][t],f[i-1][s]+abs(num[i]-j));
            }
        }
}
int main()
{
    int n,ans=100000000;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&num[i]);
    for(int i=1;i<=100;i++)
    {
        for(int j=0;j<o;j++)
        if(i%p[j]==0) st[i]|=1<<j;
        for(int j=o;j<=25;j++)
        if(i==p[j]) st[i]=-1;
    }
    sort(num+1,num+n+1);
    check(n);
    for(int i=n;i>=1 && n-i<=10;i--)
    {
        int res=1000000000;
        for(int j=0;j<1<<o;j++) res=min(res,f[i][j]);
        for(int j=i+1;j<=n;j++) res+=abs(p[o+j-i-1]-num[j]);
        ans=min(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}
```
