#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        int c=n/k;
        if(c>=m){printf("%d\n",m);continue;}
        m-=c;m=(m+k-2)/(k-1);
        printf("%d\n",c-m);
    }
    return 0;
}