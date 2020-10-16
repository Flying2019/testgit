### [链接](http://codeforces.com/problemset/problem/908/G)
看到 $n\leq 10^{700}$，考虑数位dp。

可以发现一个数字的贡献只与位置和该数字有关。又可以发现，一个数字的位置只与比它大的数字个数有关。

所以我们不妨枚举数字 $k$，设 $f_{i,j,0/1}$ 表示前 $i$ 个数字中有 $j$ 个大于等于 $k$，是否小于原数字相等，直接转移处理。

可以发现，最后 $k$ 的答案就是 $f_{n,i,0/1}\times{111\dots 1(\text{i个1})}$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 710
#define mod 1000000007
using namespace std;
int f[N][N][2],k;
char s[N];
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    int ans=0;
    for(k=1;k<=9;k++)
    {
        memset(f,0,sizeof(f));
        f[0][0][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=0;j<i;j++)
                for(int o=0;o<=1;o++)
                    for(int p=0;p<=(o?9:s[i]-'0');p++)
                    f[i][j+(p>=k)][o || (p<s[i]-'0')]=(f[i][j+(p>=k)][o || (p<s[i]-'0')]+f[i-1][j][o])%mod;
        for(int i=1,p=1;i<=n;i++,p=(10ll*p+1)%mod) ans=(ans+1ll*p*(f[n][i][0]+f[n][i][1])%mod)%mod;
    }
    printf("%d\n",ans);
    return 0;
}
```
