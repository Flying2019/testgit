#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int a[N];
int main()
{
    int n;
    ll s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i];
    ll sum=a[1],cnt=1;
    for(int i=2;i<=n;i++) if(a[1]>=2*a[i]) sum+=a[i],cnt++;
    if(sum*2<=s){puts("0");return 0;}
    else printf("%d\n1",cnt);
    for(int i=2;i<=n;i++)
    if(a[1]>=2*a[i]) printf(" %d",i);
    return 0;
}