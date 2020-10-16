### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/F)
### ��Ŀ����
����һ������Ϊ $n\ (n\leq 100)$ ������ $a_i$����֤ $a_i\in\ [1,100]$����һ����ȫ���ʵ����� $b_i$��ʹ�� $\displaystyle\sum_{i=1}^{n}|b_i-a_i|$ ��С��
### ���
���ǻ��ʾ���û��һ�������������������������г��ֹ������ҿ��Է��֣����һ������ $>100$ ��Ȼ����ѡ�����Կ�����״ѹdp��

����1~100��������25����ֱ��dp��Ȼ��TLE�����ǿ��Է��֣�1~50������ֻ��15����

����һ�����ʣ�����һ����������50����Ȼ�����ֻ�ᵥ�����֡���Ȼ���������ѡ����������������ѡ��С��һ�����š�

ͬʱ���������һ������50����������Ҫһ�� $a_i$ ȥƥ�䣬ѡ����һ��������

���Կ����Ƚ� $a_i$ ��������С��50�����������ǰ $i$ �����Ľ����Ȼ����̰��ѡ�����50��������������� $j$ �����ʹ���50������ƥ�����С���ۡ��򵥴����ɡ�

���Ӷ� $O(n*a*2^{15})$��
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
