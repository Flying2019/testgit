#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 500010
using namespace std;
int s[N];
int op[N],x[N],y[N];
int main()
{
    srand(time(0));
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n/2+1;i++) s[i]=s[n-i+1]=rand()%m+1;
    int t=0,sm=0;
    for(t=1;sm<n;t++) op[t]=rand()%2+1,sm+=op[t];
    --t;
    if(sm>n) op[t]--;
    printf("%d %d\n",t,m);
    for(int i=1,j=1;i<=t;i++,j++)
    {
        printf("%d %d",op[i],s[j]);
        if(op[i]==1) puts("");
        else printf(" %d\n",s[j+1]),j++;
    }
    return 0;
}