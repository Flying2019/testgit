#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define N 100010
using namespace std;
int a[N];
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n*m;i++) a[i]=i;
    random_shuffle(a+1,a+n*m+1);
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=m;j++) printf("%d ",a[(i-1)*m+j]);
    return 0;
}