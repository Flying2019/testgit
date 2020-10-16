### [����](http://115.236.49.52:83/contest/1583/problem/1)
���������Ķ��塣�� $f_n$ ��ʾ $n$ ��������з������ܺͣ���ô�� $g_n=\frac{f_n}{(n-1)!}$��

������ $f_n$�����ݶ��壬$f_n$ �����з��������е����ȵ�ƽ���ͣ�����

$$f_n=\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{deg_i^2}$$

����ת�ƣ��������¼���һ���㣬��ô����������ǰ���ߣ�����ö�� $fa$������

$$f_{n+1}=\sum_{u=0}^{n-1}\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{\left(deg_i+[i=u]\right)^2}$$

�����𿪿ɵã�

$$f_{n+1}=nf_n+2\sum_{deg\text{ is possible}}\sum_{i=0}^{n-1}{deg_i}+n\sum_{deg\text{ is possible}}1$$

�����������ʣ���Ȼ�У�

$$\sum_{deg\text{ is possible}}1=(n-1)!$$

$$\sum_{i=0}^{n-1}{deg_i}=2(n-1)$$

����ԭʽ�ɵã�

$$f_{n+1}=nf_n+4(n-1)(n-1)!+2\times n!$$

���� $g_n$ ��

$$g_{n+1}=\frac{f_{n+1}}{n!}$$

$$=\frac{nf_n+4(n-1)(n-1)!+2\times n!}{n!}$$

$$=\frac{f_n}{(n-1)!}-\frac{4}{n}+6$$

$$=g_n-\frac{4}{n}+6$$

������Ȼ�ɵ����մ𰸡�

ʱ�临�Ӷ� $O(n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define ll long long
#define db double
using namespace std;
db g[N];
int main()
{
    int n;
    scanf("%d",&n);
    if(n>=N-10)
    {
        double ans=2*n-2+4*(n-2);
        for(int i=2;i<=n-1;i++)
        ans-=4.0/i;
        printf("%.6lf\n",ans);
        return 0;
    }
    g[1]=0;
    g[2]=2;
    for(int i=2;i<n;i++)
    g[i+1]=g[i]+4.0*(i-1)/i+2.0;
    printf("%.6lf",g[n]);
    return 0;
}
```
