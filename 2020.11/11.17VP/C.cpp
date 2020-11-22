#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
using namespace std;
int a[N];
int op[N],l[N],r[N];
bool dn[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&op[i],&l[i],&r[i]);
        if(op[i]==1)
            for(int j=l[i];j<r[i];j++) dn[j]=true;
    }
    for(int i=1;i<=m;i++)
    if(op[i]==0)
    {
        bool hv=true;
        for(int j=l[i];j<r[i];j++) hv&=dn[j];
        if(hv){puts("NO");return 0;}
    }
    puts("YES");
    int u=n+1;
    for(int i=1;i<=n;i++)
    printf("%d ",u-=!dn[i-1]);
    return 0;
}