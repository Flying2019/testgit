#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
int res[N];
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    if(b<a)
    {
        int tt=0;
        for(int i=1;i<=a;i++) res[i]=i,tt+=i;
        for(int i=1;i<b;i++) res[a+i]=-i,tt-=i;
        res[a+b]=-tt;
    }
    else
    {
        int tt=0;
        for(int i=1;i<=b;i++) res[i]=-i,tt-=i;
        for(int i=1;i<a;i++) res[b+i]=i,tt+=i;
        res[a+b]=-tt;
    }
    for(int i=1;i<=a+b;i++) printf("%d ",res[i]);
    return 0;
}