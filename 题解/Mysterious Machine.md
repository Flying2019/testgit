### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102664/problem/D)
### ��Ŀ����
����3��01�ַ���A,B,C������ $f(a,b)$ ��ʾ $a,b$ ������������У����� $f(A,B)=a,\ f(B,C)=b,\ f(A,C)=c$
### ���
�������е��鷳�������������ó������ơ�

�������� $a\leq b\leq c$

���� $len(A)=c,\ len(B)=b,\ len(C)$ �������ơ�������A,B��C�������С�������ֻҪ $f(A,B)=a$ ���ɡ�

������򵥵ķ�ʽ����Aȫ��1��Bǰa����1�����涼��0����ȻCֻ��Ҫ5000��1+5000��0���ɡ�
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
