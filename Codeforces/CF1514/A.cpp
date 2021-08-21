#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int a[N];
bool b[N];
int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i*i<=N-10;i++) b[i*i]=true;
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        bool can=false;
        for(int i=1;i<=n;i++)
        {
            int c;
            scanf("%d",&c);
            if(!b[c]) can=true;
        }
        puts(can?"YES":"NO");
    }
    return 0;
}