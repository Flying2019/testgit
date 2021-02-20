#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int a[N],b[N];
int w[2][N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    long long ans=0;
    for(int i=1;i<=n;i++) ans+=a[i];
    for(int i=1;i<=n;i++) w[i&1][(i+1)/2]=b[i]-a[i];
    sort(w[0]+1,w[0]+n/2+1,greater<int>());
    sort(w[1]+1,w[1]+n/2+1,greater<int>());
    for(int i=1;i<=n/2;i++)
    if(w[0][i]+w[1][i]>=0) ans+=w[0][i]+w[1][i];
    else break;
    printf("%lld\n",ans);
    return 0;
}