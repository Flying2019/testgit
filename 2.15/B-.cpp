#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int f[20],g[20];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) f[i]=i;
    do
    {
        bool can=true;
        for(int i=1;i<=n;i++) g[f[i]]=i;
        for(int i=1;i<=n;i++)
        if((f[i]-g[i])%2==0) can=false;
        if(can)
        {
            for(int i=1;i<=n;i++) printf("%d ",f[i]);
            break;
        }
    }while(next_permutation(f+1,f+n+1));
    return 0;
}