#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
int x[N],n,s;
ll p[N];
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++) scanf("%d%lld",&x[i],&p[i]);
    int l=1,r=n,op=p[1]>=p[n];
    ll ans=0;
    while(l<=r)
    {
        if(x[l]>s){ans+=x[r]-s;break;}
        if(x[r]<s){ans+=s-x[l];break;}
        if(p[l]>=p[r]) p[l]+=p[r],ans+=op*(x[r]-x[l]),op=0,r--;
        else p[r]+=p[l],ans+=(1-op)*(x[r]-x[l]),op=1,l++;
    }
    printf("%lld\n",ans);
    return 0;
}