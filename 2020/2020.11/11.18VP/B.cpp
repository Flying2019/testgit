#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
char s[N];
int p[N],sf[N];
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=2;i<=n;i++) p[i]=sf[i-1]=(s[i]=='v' && s[i-1]=='v');
    for(int i=1;i<=n;i++) p[i]+=p[i-1];
    for(int i=n;i;i--) sf[i]+=sf[i+1];
    long long ans=0;
    for(int i=1;i<=n;i++)
    if(s[i]=='o') ans+=1ll*p[i]*sf[i];
    printf("%lld",ans);
    return 0;
}