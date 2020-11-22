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
        int n,m,t;
        scanf("%d%d%d",&n,&m,&t);
        printf("%d\n",n-min(m,t)+1);
    }
    return 0;
}