#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int t=(a+b)/(min(a,b)+1),l=0,r=a+b+1,q=a+b+1;
        auto calc1=[&](int x){return a-x/(t+1)*t-x%(t+1);};
        auto calc2=[&](int x){return b-x/(t+1);};
        auto check=[&](int x){return calc2(x)<=1ll*calc1(x)*t;};
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid)) l=mid+1;
            else r=mid-1,q=mid;
        }
        int k=q+calc2(q)-calc1(q)*t+1;
        for(int i=c;i<=min(d,q);i++) putchar(i%(t+1)?'A':'B');
        for(int i=max(c,q+1);i<=d;i++) putchar((i-k)%(t+1)?'B':'A');
        puts("");
    }
    return 0;
}