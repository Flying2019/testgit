#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 200010
#define inf 10000000000ll
#define abs(x) ((x)>0?(x):-(x))
using namespace std;
ll a[N],b[N],res;
int ans[N],ta,n;
int nxt[N],pre[N];bool vis[N];
void erase(int x){pre[nxt[x]]=pre[x];nxt[pre[x]]=nxt[x];}
void work(int x)
{
    if(x>n) return;
    vis[x]=true;
    res+=abs(b[x]-a[x]);
    if(a[x]>=b[x]){ans[++ta]=x;erase(x);return;}
    while(abs(a[x]-b[x])>abs(a[nxt[x]]-b[x])) work(nxt[x]);
    ans[++ta]=x;erase(x);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]),nxt[i]=i+1,pre[i]=i-1;
    a[0]=-inf,a[n+1]=inf;nxt[n+1]=n+1;
    for(int i=1;i<=n;i++)
    if(!vis[i]) work(i);
    printf("%lld\n",res);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}