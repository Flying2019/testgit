### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/E)
### ��Ŀ����
���� $n$ �������������⽻���ַ�����λ�á�ѯ���ж�����˳��,�����ϵ��ַ����Ĳ�ͬ�����и���Ϊż����
### ���
����һ�����Ĳ�ͬ�����и�����ô�㡣

�� $f_{i,j}$ ��ʾǰ $i$ ���ַ���ɵ��ַ������� $j$ ��β�Ĳ�ͬ�����и�����$\text{sum}$ ��ʾ��ǰ�𰸡�

������� $s_i=x$�������Ƴ� $f_{i,j}=f_{i-1,j}+sum_{i-1},\ sum_i=sum_{i-1}*2-f_{i-1,j}$�������������б��ʲ�ͬ���ַ������������һ���ַ�Ҳ���Ǳ��ʲ�ͬ�ġ�

����ѯ�ʵ�����ż�ԣ����Կ��� $\mod 2$�����Է��� $f_{i,j}=f_{i-1,j}+[\ j=x\ ]sum_{i-1},\ sum_i=f_{i-1,j}$�������ǽ� $f_x$ ��� $sum$ ������

�ֿ��Է��ֳ�ʼ $f_{i,j}=0,\ sum_0=1$�����Է���һ�� $f$ ��ֻ��һλΪ1��������Ȼ����dp��

������ $f_{s,j}$  ��ʾʹ�� $s$ �����ڵ��ַ������������1��λ���� $j$ �ķ�������������Ϊ $f_{s,0}$ ��ʾ $sum$��

��Ȼ�ɵ�״ѹdp���̡���ת�Ƽ��ɡ����Ӷ� $O(2^n*26*n)$��
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
