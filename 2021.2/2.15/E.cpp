#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 2000010
#define ll long long
using namespace std;
int p[N],cnt;
bool pr[N];int mu[N],s[N];
void init(int n=N-10)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0){mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++) s[i]=s[i-1]+mu[i];
}
map<int,int>sm;
int get_sum(int n)
{
    if(n<=N-10) return s[n];
    if(sm.count(n)) return sm[n];
    int res=1;
    for(int l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        res-=(r-l+1)*get_sum(n/l);
    }
    return sm[n]=res;
}
//\sum_{i=0}^{n}\lfloor\frac{ai+b}{c}\rfloor
ll solve(int n,int a,int b,int c)
{
    if(n<0) return 0;if(n==0) return b/c;
    if(!a) return 1ll*(b/c)*(n+1);
    if(a>=c || b>=c) return solve(n,a%c,b%c,c)+1ll*n*(n+1)/2*(a/c)+1ll*(n+1)*(b/c);
    ll m=(1ll*a*n+b)/c;
    return n*m-solve(m-1,c,c-b-1,a);
}
//\sum_{a>=1}\sum_{b>=1}ax+b(x+y)<=n
ll work(int x,int y,int n){return solve(n/x-1,x,n%x,y);}
int main()
{
    int t,n;
    scanf("%d%d",&t,&n);
    init();
    while(t --> 0)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>n || y>n){puts("0");continue;}
        if(x<=y){puts("1");continue;}
        y+=x;
        if(y>n){puts("2");continue;}
        ll ans=4;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=4ll*(get_sum(r)-get_sum(l-1))*work(x,y,n/l);
        }
        printf("%lld\n",ans);
    }
    return 0;
}