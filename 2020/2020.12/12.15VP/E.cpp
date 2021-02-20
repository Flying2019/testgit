#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 1000000007
using namespace std;
char s[N];
int f[N],g[3]={0,-1,-1};
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1),p=0;
    bool hv=false;
    for(int i=2;i<=n;i++)
    if(s[i]==s[i-1]) hv=true;
    if(!hv){puts("1");return 0;}
    f[0]=1;
    for(int i=1;i<=n;i++)
    {
        p=(p+s[i]-'a'+1)%3;
        f[i]=!p && i!=n; g[p]=i;
        if(~g[(p+1)%3]) (f[i]+=f[g[(p+1)%3]])%=mod;
        if(~g[(p+2)%3]) (f[i]+=f[g[(p+2)%3]])%=mod;
    }
    printf("%d\n",f[n]);
    return 0;
}