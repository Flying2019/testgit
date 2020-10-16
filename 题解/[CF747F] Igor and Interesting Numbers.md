### [链接](http://codeforces.com/problemset/problem/747/F)
考虑dp。但是这里状态比较难定义（直接状压好像也可以）。

考虑主要问题在于前导0.如果没有前导0，后面的其实可以直接计数dp求出。

那么一种比较暴力的方式就是枚举第一位。我们不妨枚举第一位和第一位放的数，那么后面的部分可以dp求出总方案数。

首先我们先找到第一个可行的长度。这个直接枚举第一位放的东西，考虑剩下可行的放置方式即可。

再考虑从大往小填，如果当前方案数比 $n$ 大，那么就填上，然后放下一位。

复杂度 $O(\log^4 n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
#define N 24
using namespace std;
ll C[N][N];
int tot[N];
ll f[N][N];
ll work(int n)
{
    if(n==0) return 1;
    memset(f,0,sizeof(f));f[0][0]=1;
    for(int i=1;i<=16;i++)
        for(int j=0;j<=n;j++)
            for(int k=0;k<=tot[i] && k<=j;k++)
                f[i][j]+=f[i-1][j-k]*C[j][k];
    return f[16][n];
}
char s[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    C[0][0]=1;
    for(int i=1;i<=N-2;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    for(int i=1;i<=16;i++) tot[i]=m;
    int k=1;
    for(k=1;k<=18;k++)
    {
        ll res=0;
        for(int i=2;i<=16;i++)
        if(tot[i])
        {
            tot[i]--;
            res+=work(k-1);
            tot[i]++;
        }
        if(n<=res) break;
        n-=res;
    }
    for(int i=0;i<k;i++) s[i]='0';
    for(int i=k;i>=1;i--)
    {
        for(int j=1;j<=16;j++)
        if((i!=k || j!=1) && tot[j])
        {
            tot[j]--;
            ll res=work(i-1);
            if(res>=n){s[k-i]=j>10?'a'+j-11:'0'+j-1;break;}
            tot[j]++;
            n-=res;
        }
    }
    printf("%s",s);
    return 0;
}
```
