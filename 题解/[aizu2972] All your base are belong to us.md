### [����](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2972)
### ��Ŀ����
����ƽ���� $n$ ���㣬��һ���㣬ʹ���䵽�� $n$ ������ǰ $k$ Զ�ľ������С��

Ҫ�󾫶� $\leq 10^{-3}$��
### ���
�������Ӧ��������֮����㷨������������̫���ˣ�ֱ�Ӳ�����������ɽ���㷨��

���Ƕ���$k=n$ ���������ʱ��Ҫ�����ʵ��һ������㣬������Բ���ģ����ѧ�����ķ�����

����������һ�����ӣ����е㶼����һ����������һ�����Ӳ����ϵ��ص�������ӵ���һ������һ��

Ȼ�󲻶��ж�������˶�����Ȼ��΢�����ɡ�

��[JSOI2004 ƽ���](https://www.luogu.com.cn/problem/P1337)��
![](https://cdn.luogu.com.cn/upload/pic/148.png)

�������������������Ҳ������ô��������ֻ����Զ�� $k$ �����������ӣ�Ȼ�������Щ��ģ��һ�¼��ɡ�

ͬʱΪ�˷��㣬���ǹ涨���ĳ�����������͵� $k$ ��ĵ��������ľ���**���**����ô���ǰ������Ҳ�������ӡ�

ֱ�����������ܻ�T������һ��ʼ��ǰ�����Ŀ��㻹��Զ��������������ģ���˻��˼·����ʼʱ�ƶ�����Ƚϴ󣬺���Խ��ԽС���������Խ�������ʱ�䡣

���Ӷ�ʮ����ѧ�������������ľ�������ʮ��С������������������ $10^{-6}$ ���ҵľ��ȣ�������ȫû�����⡣��ʵҲ֤�����ܵ÷ɿ졣
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 210
#define db double
#define eps 1e-5
using namespace std;
struct node{
    db x,y;
    node(db X=0,db Y=0):x(X),y(Y){}
    node operator <(const node a)const{return x==a.x?y<a.y:x<a.x;}
    node operator +(const node a)const{return node(x+a.x,y+a.y);}
    node operator -(const node a)const{return node(x-a.x,y-a.y);}
    node operator *(const db a)const{return node(x*a,y*a);}
    node operator /(const db a)const{return node(x*1.0/a,y*1.0/a);}
}p[N];
int n,k;
db dis(node a){return sqrt(a.x*a.x+a.y*a.y);}
node stb(node a){if(abs(a.x)<=eps && abs(a.y)<=eps) return node(0,0);return a/dis(a);}
struct pnode{
    int id;
    db d;
    bool operator <(const pnode a)const{return d<a.d;}
}a[N];
node check(node o)
{
    for(int i=1;i<=n;i++)
    a[i]=(pnode){i,dis(p[i]-o)};
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    node res=node(0,0);
    for(int i=1;i<=k;i++) res=res+stb(p[a[i].id]-o);
    for(int i=k+1;i<=n;i++)
    if(abs(a[i].d-a[k].d)<=eps) res=res+stb(p[a[i].id]-o);
    return res;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    scanf("%f%f",&p[i].x,&p[i].y);
    node ans=p[1];
    db T=10;
    while(abs(T)>eps)
    {
        node o=check(ans);
        if(dis(o)<=1e-5) break;
        o=o*T;
        ans=ans+o;
        T=T*0.995;
    }
    for(int i=1;i<=n;i++)
    a[i]=(pnode){i,dis(p[i]-ans)};
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    db res=0;
    for(int i=1;i<=k;i++) res=res+a[i].d;
    printf("%.4f",res);
    return 0;
}
```
