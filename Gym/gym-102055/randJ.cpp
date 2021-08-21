#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define N 100010
using namespace std;
int ban[N];
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    puts("5");
    for(int t=1;t<=5;t++)
    {
        printf("%d %d\n",n,m);
        for(int i=1;i<=n;i++) printf("%d ",rand()%3+1),ban[i]=i;puts("");
        random_shuffle(ban+1,ban+n+1);
        sort(ban+1,ban+m+1);
        for(int i=1;i<=m;i++) printf("%d ",ban[i]);puts("");
    }
    return 0;
}