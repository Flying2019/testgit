#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
int a[N],x[N],op[N],l[N],r[N];
bool vis[N];
int main()
{
    int n,L;
    scanf("%d%d",&n,&L);L*=2;
    long long ans=0;
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),ans+=a[i]/L,a[i]%=L;
    for(int i=1;i<=n;i++)
    if(!a[i]) --ans,vis[i]=true;
    else l[i]=L>=a[i]+2ll*x[i],r[i]=2*x[i]>=a[i],vis[i]=!l[i] && !r[i];
    ans+=n+!l[n];
    int s=0,c=0,p=n;
    for(int i=1;i<n;i++)
    if(!vis[i])
    {
        if(!l[i]){p=i;break;}
        if(r[i]) ++c;
        else if(c) --c,--ans;
    }
    s=c;
    for(int i=n-1;i>=p;i--)
    if(!vis[i])
    {
        if(!r[i]) break;
        if(l[i]) ++c;
        else if(c>s) --c,--ans;
    }
    ans-=c/2;
    printf("%lld\n",L*ans);
    return 0;
}