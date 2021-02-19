#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#define mod 998244353
using namespace std;
char s[N];
int c[8];//r,g,b,gb,rb,rg
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    int ans=1;
    for(int i=1;i<=n;i++) ans=1ll*ans*i%mod;
    n*=3;
    for(int i=1;i<=n;i++)
    {
        int u=(s[i]=='R'?0:(s[i]=='G'?1:2));
        if(c[u+3]) ans=1ll*ans*(c[u+3]--)%mod;
        else if(c[(u+1)%3]) ans=1ll*ans*(c[(u+1)%3]--)%mod,c[(u+2)%3+3]++;
        else if(c[(u+2)%3]) ans=1ll*ans*(c[(u+2)%3]--)%mod,c[(u+1)%3+3]++;
        else c[u]++;
    }
    printf("%d\n",ans);
    return 0;
}