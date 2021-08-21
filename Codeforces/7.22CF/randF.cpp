#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#define N 300010
using namespace std;
int a[N];
int main()
{
    srand(time(0));
    int n=200000,m=300000;
    for(int i=1;i<=m;i++) a[i]=i;
    random_shuffle(a+1,a+m+1);
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return 0;
}