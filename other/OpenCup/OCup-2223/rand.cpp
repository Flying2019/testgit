#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#define N 400010
using namespace std;
struct road{
    int x,y;
}a[N];
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d %d\n",n,m);
    int t=0;
    for(int i=1;i<=n;i++) a[++t]=(road){i,i%n+1};
    while(t<m) a[++t]=(road){rand()%n+1,rand()%n+1};
    random_shuffle(a+1,a+t+1);
    for(int i=1;i<=m;i++) printf("%d %d\n",a[i].x,a[i].y);
    return 0;
}