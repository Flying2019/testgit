#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
using namespace std;
char s[N],t[N];
int x[N],xt,y[N],yt,n;
int get(int a[],int at,int i){return i<0?0:i>at?n:a[i];}
int main()
{
    scanf("%d",&n);
    scanf("%s%s",s+1,t+1);
    for(int i=1;i<n;i++){if(s[i]!=s[i+1]) x[++xt]=i;if(t[i]!=t[i+1]) y[++yt]=i;}
    int ans=n*n,m=xt+yt;
    for(int i=(xt&1)^(s[1]!=t[1]);i<=m+1;i+=2)
    {
        int res=0;
        for(int j=-m;j<=m;j++) res+=abs(get(x,xt,j)-get(y,yt,i-xt+j));
        ans=min(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}