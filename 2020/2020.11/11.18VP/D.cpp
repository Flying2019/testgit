#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
using namespace std;
bool check(int x)
{
    for(int i=2;1ll*i*i<=x;i++)
    if(x%i==0) return false;
    return true;
}
int main()
{
    int n;
    scanf("%d",&n);
    int m=n,t=0;
    while(!check(m)) ++m,++t;
    printf("%d\n",m);
    for(int i=1;i<=n;i++) printf("%d %d\n",i,i%n+1);
    for(int i=1;i<=t;i++) printf("%d %d\n",i,n-i);
    return 0;
}