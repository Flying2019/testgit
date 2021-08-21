#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
using namespace std;
int main()
{
    int n,t;
    scanf("%d%d",&n,&t);
    int pre=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        if(x>pre) pre=x;
        else
        {
            while(x<pre) x+=t;
            pre=x;
        }
    }
    printf("%d\n",pre);
    return 0;
}