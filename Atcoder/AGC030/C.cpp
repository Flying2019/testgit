#include<iostream>
#include<cstdio>
#include<cstring>
#define N 510
using namespace std;
int main()
{
    int k;
    scanf("%d",&k);
    if(k<=500){printf("%d\n",k);for(int i=1;i<=k;i++,puts("")) for(int j=1;j<=k;j++) printf("%d ",i);return 0;}
    int n=500;k-=n;
    printf("%d\n",n);
    for(int i=0;i<n;i++,puts(""))
        for(int j=0;j<n;j++)
        {
            int c=(i+j)%n;
            if(i%2==0 && c<k) c+=n;
            printf("%d ",c+1);
        }
    return 0;
}