#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 100010
using namespace std;
int main()
{
    srand(time(0));
    puts("10");
    for(int i=1;i<=10;i++)
    {
        int a=rand()%500+1,b=rand()%500+2;
        a=a+b-rand()%10;
        a=max(a,1);
        int c=rand()%(a+b)+1,d=rand()%(a+b)+a;
        if(c>d) swap(c,d);
        printf("%d %d %d %d\n",a,b,c,d);
    }
    return 0;
}