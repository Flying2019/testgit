#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<ctime>
#define N 100010
using namespace std;
vector<int>c[N];
int id[N];
int rand0(){return (1ll*rand()<<24^rand())%1000000003;}
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    int m1=0,m2=0,n1=n/2,n0=n-n1;
    int tt=0;
    for(int i=1;i<=n1;i++)
    {
        int d=1;
        if(rand()%2 || !n0) d=1;
        else if(rand()%5) d=rand()%3+1;
        else d=rand()%n0+1;
        if(d-1>n0) d=1;
        m1+=d==1?0:d;n0-=d-1;
        for(int p=0;p<d;p++) c[i].push_back(++tt);
    }
    n-=n0;
    int n2=1;
    for(int i=1;i<=n1;i++) id[i]=i;
    random_shuffle(id+1,id+n1+1);
    n2=min(rand()%(n1/2+1)+n1/2,n1);
    m=m1+n2-1;
    printf("1\n%d %d %d\n",n,m,rand()%min(n,1000)+1);
    for(int i=1;i<=n1;i++)
    if(c[i].size()!=1)
        for(int p=0;p<c[i].size();p++) printf("%d %d %d\n",c[i][p],c[i][(p+1)%c[i].size()],rand0());
    for(int i=2;i<=n2;i++)
    {
        int v=id[i];
        int u=id[rand()%(i-1)+1];
        printf("%d %d %d\n",c[u][rand()%c[u].size()],c[v][rand()%c[v].size()],rand0());
    }
    return 0;
}