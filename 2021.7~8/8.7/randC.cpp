#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 100010
using namespace std;
int rand0(){return (1ll*rand()<<31^rand())%1000000000;}
int main()
{
    srand(time(0));
    int n,m,t=10000;
    scanf("%d%d",&n,&m);
    printf("%d\n",t);
    while(t --> 0)
    printf("%d %d %d %d\n",rand()%n+1,m+rand()%4,rand0()%m+1,rand0()%m+1);
    return 0;
}