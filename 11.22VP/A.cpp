#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int a[N];
int r[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int r=0;
    for(int i=1;i<=n;i++)
    if(a[i]%2==0) printf("%d\n",a[i]/2);
    else if(r) printf("%d\n",(a[i]+1)/2),r=0;
    else printf("%d\n",(a[i]-1)/2),r=1;
    return 0;
}