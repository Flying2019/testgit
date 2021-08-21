#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 100010
using namespace std;
int main()
{
    srand(time(0));
    int n,m,c;
    scanf("%d%d%d",&n,&m,&c);
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d ",rand()%c+1);puts("");
    printf("%d\n",m);
    for(int i=1;i<=m;i++) printf("%d ",rand()%c+1);puts("");
    for(int i=1;i<=m;i++) putchar(rand()&1?'S':'B');
    return 0;
}