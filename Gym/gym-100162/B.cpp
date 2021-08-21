#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2000010
using namespace std;
char s[N];
int nxt[N],ans[N];
bool vis[N];
int main()
{
    int T=0;
    while(cin>>s+1)
    {
        int n=strlen(s+1);
        if(!n) break;
        for(int i=1;i<=n;i++) s[i+n]=s[i];
        for(int i=0;i<=n*2;i++) nxt[i]=ans[i]=vis[i]=0;
        s[n*2+1]='\0';
        for(int l=1,r=1;l<=n*2;l=r+1)
        {
            for(r=l;r<n*2 && s[r]!=s[r+1];r++);
            nxt[l]=l-1;int p=l-1;
            for(int i=l+1;i<=r;i++)
            {
                while(p>=l && s[i]!=s[p+1]) p=nxt[p];
                if(s[p+1]==s[i]) p++;
                nxt[i]=p;
            }
            for(int i=l;i<=r;i++) vis[i]=0;
            for(int i=nxt[r];i>=l;i=nxt[i]) vis[i]=true;
            for(int i=l;i<=r;i++) if(!vis[i] && n-r+i-1>=0) ans[n-r+i-1]=true;
        }
        printf("Case %d: ",++T);
        for(int i=0;i<n;i++) putchar('0'+ans[i]);
        puts("");
    }
    return 0;
}