#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define N 1010
using namespace std;
int p[N];
bool f[N];
int main()
{
    srand(1019260817);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) p[i]=i;
    for(int _=1;;_++)
    {
        random_shuffle(p+1,p+n+1);
        int w=n;
        for(int i=1;i<=n;i++)
        {
            printf("0 %d\n",p[i]);fflush(stdout);
            int v;
            scanf("%d",&v);
            if(v<w) f[p[i]]=true;
            w=v;
        }
        int c=0;
        for(int i=1;i<=n && c>=0;i++)
        if(!f[i]){if(c==0) c=i;else c=-1;}
        if(c!=-1){printf("1 %d\n",c);return 0;}
    }
    return 0;
}