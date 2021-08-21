#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
ll a[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        priority_queue<ll>q;
        int n,m;scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) scanf("%lld",&a[i]);
        sort(a,a+n);
        for(int i=0;i<n;i++) a[i]-=1ll*i*m;
        ll ans=0;
        for(int i=0;i<n;i++) if(a[i]<0) ans-=a[i],a[i]=0;
        for(int i=0;i<n;i++)
            ans+=a[i],q.push(a[i]),q.push(a[i]),q.pop();
        while(!q.empty()) ans-=q.top(),q.pop();
        printf("%lld\n",ans);
    }
    return 0;
}