### [����](http://115.236.49.52:83/contest/1530/problem/2)
��Ȼ�������ۡ��� $n=1$ ʱ����Ȼ��ɾ��1���š����Է��֣���ʱ��� $c=3$ ��ô����6��������4��

���ǵ� $n>1,\ c>2$ ʱ����Ȼ $\forall \ x\leq n+1,\ 2x\leq n\times c$�����ݸ���ԭ�����֪����ʱɾ�� $[1,n]$ ���ţ���ô��Ϊ $2\times(n+1)$��

����ʣ�����������Է��֣� $\forall \ x\leq n,\ 2x\leq n\times c$����Ȼ������ $x$ �� $2\times x$��������Ҫɾ������һ����

����Ϊ��Ȼ�� $\forall \ y\geq 1,\ lcm(x,y)\leq lcm(2x,y)$��������Ȼɾ�� $x$ ����������ֱ��ɾ�� $[1,n]$ ���š�Ҳ��������Ҫ��� $\displaystyle\min_{x,y\in[n+1,2n]}\{lcm(x,y)\}$��

��Ȼ�� $n$ �Ƚ�Сʱ��������һ�� $O(Tn^2)$ ������������Ȼ����ͨ�����⡣

���Է��֣��� $n$ �㹻��ʱ��Ҫʹ $x,y$ ������С������Ӧ�������ܵ�ʹ $gcd(x,y)$ ���

������˵����� $x|a,\ x'|b,\ (a<b,\ x'-x=\Delta>0)$���Ҳ����� $x_0|a,\ x_0'|b$ ���� $x_0< x,\ x'_0<x'$��

�������Ҫ�õ���Сֵ����ȻҪȡ $x+a,\ x'+b$��

��Ȼ�� $lcm(x,x+a)=\frac {x^2} a+x,\ lcm(x',x'+b)=\frac {x'^2} b+x'$��

���� $n$ �㹻��$\Delta$ ��ʵ���� $n$ ��Ⱥ�С��������Ȼ�����Ǹ�ʽ�Ӹ�СһЩ��

��Ȼ����Ϊ $n$ ������� $\lfloor\frac {n+2} 2\rfloor$�����Է��֣���������� $x=2\lfloor\frac {n+2} 2\rfloor$��$\text{��}=6\lfloor\frac {n+2} 2\rfloor$��

��Ȼ������㹻����ʵ��С���ײ�ֻ�� $n=5$ ʱ��������м��ɡ����Ӷ� $O(T)$��
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,c=2;
        scanf("%d%d",&n,&c);
        if(n==1){if(c==3) puts("6");else puts("4");continue;}
        if(c>2){printf("%d\n",(n+1)*2);continue;}
        if(c==2)
        {
            if(n>20){printf("%lld\n",6ll*((n+2)/2));continue;}
            long long ans=1ll*(n+1)*(n+2);
            for(int j=n+1;j<=n*2;j++)
                for(int k=j+1;k<=n*2;k++)
                ans=min(ans,1ll*j*k/gcd(j,k));
            // for(int j=1;j<=n;j++)
            // {
            //     int x=(n/j+1)*j,y=x+j;
            //     ans=min(ans,1ll*x*y/j);
            // }
            printf("%lld\n",ans);
        }
    }
}
```
