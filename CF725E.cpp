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
    for(int i=1;i<=c;i++)
    {
        int res=n;
        auto t=s.lower_bound((node){i,0});
        if(t->x==i) t->c++;
        else s.insert((node){i,1});
        while(res)
        {
            t=s.lower_bound((node){res,0});
            if(t==s.end() || t->x>res){printf("%d\n",i);return 0;}
            if(1ll*t->x*t->c<=res) res-=t->x*t->c;
            else res=res%t->x;
        }
        t=s.lower_bound((node){i,0});
        if(t->c!=1) t->c--;
        else s.erase(t);
    }
    return 0;
}