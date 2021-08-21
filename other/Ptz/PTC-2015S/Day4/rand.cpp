#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 100010
using namespace std;
int main()
{
    int n,c;
    scanf("%d%d",&n,&c);
    srand(time(0));
    int T=5;
    printf("%d\n",T);
    while(T --> 0)
    {
        for(int i=1;i<=n;i++) putchar('a'+rand()%c);
        puts("");
    }
    return 0;
}