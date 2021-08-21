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
        int n,mx,mn,av;scanf("%d%d%d%d",&n,&mx,&mn,&av);
        bool can=true;
        if(n==1 && mn!=mx) can=false;
        if(mx<av || mn>av) can=false;
        if(mx+mn*(n-1)>av*n) can=false;
        if(mn+mx*(n-1)<av*n) can=false;
        puts(can?"yes":"no");
    }
    return 0;
}