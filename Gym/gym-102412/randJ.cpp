#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#define N 200010
using namespace std;
int a[N];
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d %d\n",n,m);
    int t=0;
    for(int i=0;i<n/2;i++) a[++t]=i;
    while(t<n)
    if(rand()&1) a[++t]=rand()%(n/3);
    else a[++t]=rand()%(n*2/3);
    random_shuffle(a+1,a+t+1);
    for(int i=1;i<=t;i++) printf("%d ",a[i]);
    return 0;
}