#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define N 100010
using namespace std;
int id[N];
int fa[N];
int main()
{
    srand(time(0));
    int n=99999,m=200000;
    printf("%d %d\n",n,m);
    for(int i=1;i<n;i++) id[i]=i+1;
    for(int i=2;i<=n;i++) fa[i]=rand()%(i-1)+1;
    random_shuffle(id+1,id+n);
    for(int i=1;i<n;i++) printf("%d %d\n",i,fa[id[i]]),--m;
    for(int i=1;i<n;i++) printf("%d %d\n",i,id[i]),--m;
    // for(int i=1;i<n-1;i++) printf("%d %d\n",i,n),--m;
    while(m --> 0)
    {
        int u=rand()%(n-1)+1,v=rand()%n+1;
        printf("%d %d\n",u,v);
    }
    return 0;
}