#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
#define ld long double
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int h,c,t;
        scanf("%d%d%d",&h,&c,&t);
        if(h==t){puts("1");continue;}
        if(h+c>=t*2){puts("2");continue;}
        long long x=floor(1.0*(t-h)/(h+c-2*t));
        if(((x+1)*h+x*c-t*(2*x+1))*(2*x+3)<=(-(x+2)*h-(x+1)*c+t*(2*x+3))*(2*x+1)) printf("%d\n",2*x+1);
        else printf("%d\n",2*x+3);
    }
    return 0;
}