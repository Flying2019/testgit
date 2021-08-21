#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n;scanf("%d",&n);
        printf("Case #%d:\n",_);
        puts("YES");
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++) printf("%d %d 0 %d %d 1 %d %d\n",i,j,i,j,i,j);
    }
    return 0;
}