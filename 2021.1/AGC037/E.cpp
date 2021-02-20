#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10010
using namespace std;
char s[N];int n;
bool cmp(int x,int y){for(int i=0;i<n;i++) if(s[x-i]!=s[y-i]) return s[x-i]<s[y-i]; return false;}
int main()
{
    int k;
    scanf("%d%d",&n,&k);--k;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) s[n+i]=s[n-i+1];
    char c=s[1];int t=n+1;
    for(int i=n+2;i<=n*2;i++) if(cmp(i,t)) t=i;
    int u=0;while(s[t-u]==s[t]) u++;
    if(k>15 || (u<<k)>=n) for(int i=1;i<=n;i++) putchar(s[t]);
    else
    {
        for(int i=0;i<u<<k;i++) putchar(s[t]);
        for(int i=0;i<n-(u<<k);i++)putchar(s[t-u-i]);
    }
    return 0;
}