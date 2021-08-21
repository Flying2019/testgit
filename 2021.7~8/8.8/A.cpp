#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
using namespace std;
struct node{
    int d,k;
    bool operator <(const node a)const{return d*a.k<k*a.d;}
}p[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&p[i].d,&p[i].k);
    sort(p+1,p+n+1);
    long long a1=0,s=0;
    for(int i=1;i<=n;i++) a1+=abs(2*p[i].k*s+p[i].k*p[i].d),s+=p[i].d;
    long long a2=0;s=0;
    for(int i=n;i;i--) a2+=abs(2*p[i].k*s+p[i].k*p[i].d),s+=p[i].d;
    printf("%lld\n",max(a1,a2));
    return 0;
}