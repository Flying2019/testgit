### [链接](http://codeforces.com/problemset/problem/725/E)
首先选择太多了，考虑贪心。

假如我们选择了加入多于两枚硬币，很明显把他们俩之和加进去一定不会更差。

所以我们只选择一枚硬币。

接下来问题是如何处理能否成功。暴力做显然是不对的，给一堆1就爆炸了。

但是考虑由于 $c$ 很小，说明这种情况下不同的面额很少。

那么我们可以把相同面值的一起处理。每次我们用set找到当前剩余的可行方法中最大的那个。

然后我们暴力枚举加入的那枚硬币。总复杂度比较玄学，好像理论 $O(n\sqrt n\log n)$，实际跑的很快。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
#define N 200010
using namespace std;
int a[N],p[N];
struct node{
    mutable int x,c;
    bool operator <(const node a)const{return x==a.x?c<a.c:x>a.x;}
};
set<node>s,s0;
int main()
{
    int c,n;
    scanf("%d%d",&c,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),p[a[i]]++;
    for(int i=1;i<=c;i++)
    if(p[i]) s.insert((node){i,p[i]});
    for(int i=0;i<=c;i++)
    {
        int res=c;
        auto t=s.lower_bound((node){i,0});
        if(i)
        {
            if(t!=s.end() && t->x==i) t->c++;
            else s.insert((node){i,1});
        }
        while(res)
        {
            t=s.lower_bound((node){res,0});
            if(t==s.end() || t->x>res){printf("%d\n",i);return 0;}
            if(1ll*t->x*t->c<=res) res-=t->x*t->c,s0.insert(*t),s.erase(t);
            else res=res%t->x;
        }
        for(auto u:s0) s.insert(u);s0.clear();
        if(i)
        {
            t=s.lower_bound((node){i,0});
            if(t->c!=1) t->c--;
            else s.erase(t);
        }
    }
    puts("Greed is good");
    return 0;
}
```
