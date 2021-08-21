#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int main()
{
    int n,m=0;
    scanf("%d",&n);m=n&(-n);
    if(m==n){puts("No");return 0;}
    puts("Yes");
    for(int i=2;i<n;i+=2) printf("1 %d\n1 %d\n%d %d\n%d %d\n",i,i+n+1,i,i+1,i+n,i+n+1);
    if(!(n&1)) printf("%d %d\n%d %d\n",n,n+m+1,n*2,n-m);
    printf("%d 3\n",n+1);
    return 0;
}