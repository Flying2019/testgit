#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1010
#define ll long long
using namespace std;
int pr[N*10],tot;
bool p[N*10];
void init(int n=N*10-10)
{
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) pr[++tot]=i;
        for(int j=1;j<=tot && pr[j]*i<=n;j++)
        {
            p[pr[j]*i]=true;
            if(i%pr[j]==0) break;
        }
    }
}
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll lcm(ll x,ll y){return x && y?x/gcd(x,y)*y:x+y;}
ll a[N][N];
int main()
{
    int n;
    scanf("%d",&n);
    if(n==2){puts("4 7\n23 10");return 0;}
    init();
    for(int i=1;i<=n;i++)
        for(int j=(~i&1)+1;j<=n;j+=2)
        a[i][j]=1ll*pr[(i+j)/2]*pr[n+(i-j)/2+(n+1)/2];
    for(int i=1;i<=n;i++)
        for(int j=(i&1)+1;j<=n;j+=2)
        a[i][j]=lcm(lcm(a[i-1][j],a[i+1][j]),lcm(a[i][j-1],a[i][j+1]))+1;
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++) printf("%lld ",a[i][j]);
    return 0;
}