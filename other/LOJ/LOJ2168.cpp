#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char s[N],t[N];
int nxt[N];
int border(char s[],int n)
{
    nxt[1]=0;int p=0;
    for(int i=2;i<=n;i++)
    {
        while(p && s[i]!=s[p+1]) p=nxt[p];
        if(s[i]==s[p+1]) p++;
        nxt[i]=p;
    }
    return p;
}
void make(char s[],char t[],int n)
{
    if(n==1){t[1]='0';return;}
    int p=border(s,n),r=n-p;
    if(p==0){for(int i=1;i<n;i++) t[i]='0';t[n]='1';return;}
    if(p*2>=n)
    {
        int v=r+n%r;
        make(s,t,v);
        for(int i=v+1;i<=n;i++) t[i]=t[i-r];
    }
    else
    {
        make(s,t,p);
        for(int i=r+1;i<=n;i++) t[i]=t[i-(n-p)];
        for(int i=p+1;i<=r;i++) t[i]='0';
        if(border(t,n)>p) t[r]='1';
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T --> 0)
    {
        scanf("%s",s+1);
        int n=strlen(s+1);t[n+1]='\0';
        make(s,t,n);
        printf("%s\n",t+1);
    }
    return 0;
}