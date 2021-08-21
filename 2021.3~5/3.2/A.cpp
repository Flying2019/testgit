#include<iostream>
#include<cstdio>
#include<cstring>
#define N 60
using namespace std;
int d[N],c[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);d[t]++;
    }
    d[0]++;
    for(int i=0;i<12;i++) if(d[i]>2){puts("0");return 0;}
    if(d[0]>1 || d[12]>1){puts("0");return 0;}
    int S=1<<12,ans=0;
    for(int s=0;s<S;s++)
    {
        bool can=true;
        for(int i=1;i<12;i++)
        if(d[i]!=1 && (s>>i)&1) can=false;
        if(!can) continue;
        for(int i=0;i<=24;i++) c[i]=0;
        c[12]=d[12];c[0]=c[24]=1;
        for(int i=1;i<12;i++)
        if(d[i]==2) c[i]=c[24-i]=true;
        else if(d[i]==1)
        {
            if((s>>i)&1) c[24-i]=true;
            else c[i]=true;
        }
        int pre=0,res=11111111;
        for(int i=1;i<=24;i++)
        if(c[i]) res=min(res,i-pre),pre=i;
        ans=max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}