### [����](https://www.luogu.com.cn/problem/P3424)
��Ȼ���ǿ��԰Ѷ�Ӧ���ּ����������Է��ִ�ʱ������ֻ��0,1,2����2�Ա�һ������0��

������ $2*f(i)=f(i-2)+f(i+1)$�������ȴӴ�С��������е�2����Ϊÿ����һ�Σ�2һ����ǰ�������Ը��Ӷ��ǶԵġ�

�ٿ����� $f(i-1)+f(i)=f(i+1)$���������ǴӴ�С�ҵ�һ��������1�������λ�Լ���λ�Ľ�λ������ÿ����һ��1����1�������Ը��Ӷ�Ҳ�ǶԵġ�

�ܸ��Ӷ� $O(n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int num[N];
int main()
{
    int n,p;
    scanf("%d",&n);
    for(int i=1,a;i<=n;i++) scanf("%d",&a),num[i]+=a;
    scanf("%d",&p);
    for(int i=1,a;i<=p;i++) scanf("%d",&a),num[i]+=a;
    n=max(n,p);
    while(1)
    {
        int p1=0;
        for(int i=p+3;i>=1;i--)
        if(num[i]>=2)
        {
            if(i>2) num[i-2]++,num[i+1]++,num[i]-=2,i+=2,p1=max(p1,i);
            else if(i==2) num[1]++,num[3]++,num[2]-=2,i+=2;
            else num[2]++,num[i]-=2,i+=2;
            if(num[i] && num[i+1])
            {
                num[i]--;num[i+1]--;
                int j=i+2;
                while(num[j+1]) num[j+1]--,j+=2;
                num[j]++;
            }
        }
        if(!p1) break;
        p=p1;
    }
    for(int i=N-10;i>=1;i--)
    if(num[i] && num[i+1])
    {
        num[i]--;num[i+1]--;
        int j=i+2;
        while(num[j+1]) num[j+1]--,j+=2;
        num[j]++;
    }
    int m=N-10;
    for(;!num[m];m--);
    printf("%d ",m);
    for(int i=1;i<=m;i++) printf("%d ",num[i]);
    return 0;
}
```
