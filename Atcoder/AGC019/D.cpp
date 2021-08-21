#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2010
using namespace std;
char s[N],t[N];
int l[N],r[N],mx[N],ans;
void solve(int n)
{
    // printf("%s\n%s\n",s,t);
    for(int i=0;i<n;i++)
    {
        for(r[i]=0;t[(i+r[i])%n]!='1';r[i]++);
        for(l[i]=0;t[(i-l[i]+n)%n]!='1';l[i]++);
    }
    for(int i=0;i<n;i++)
    {
        memset(mx,0,sizeof(mx));
        int res=0,m=0;
        for(int j=0;j<n;j++)
        if(s[j]!=t[(i+j)%n])
        {
            res++;
            mx[l[j]]=max(mx[l[j]],r[j]);
        }
        for(int j=n-1;j>=0;j--) ans=min(ans,2*j+m+abs(m-i)+res),m=max(m,mx[j]);
        ans=min(ans,res+m*2+i);
    }
}
int main()
{
    scanf("%s%s",s,t);
    int n=strlen(s);ans=2*n;
    bool zs=true,zt=true;
    for(int i=0;i<n;i++) if(s[i]=='1') zs=false;
    for(int i=0;i<n;i++) if(t[i]=='1') zt=false;
    if(zt){puts(zs?"0":"-1");return 0;}
    solve(n);reverse(s,s+n);reverse(t,t+n);solve(n);
    printf("%d\n",ans);
    return 0;
}