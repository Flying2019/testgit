#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define ll long long
using namespace std;
ll a[N],b[N],c[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++) scanf("%d",&a[i]);
        for(int i=0;i<m;i++) scanf("%d",&b[i]);
        sort(a,a+m),sort(b,b+m);
        ll ans=10000000000ll;
        for(int p=0;p<m;p++)
        {
            for(int i=0;i<m;i++) c[i]=(a[(i+p)%m]-b[i]+n)%n;
            sort(c,c+m);
            for(int i=0;i<m-1;i++) ans=min(ans,c[i]+(n-c[i+1])+min(c[i],n-c[i+1]));
            ans=min(ans,min(c[m-1],n-c[0]));
        }
        printf("%lld\n",ans);
    }
    return 0;
}