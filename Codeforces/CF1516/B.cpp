#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int a[N],s[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=s[i-1]^a[i];
        if(s==0){puts("YES");continue;}
        bool can=false;
        for(int i=1;i<=n && !can;i++)
            for(int j=i;j<=n && !can;j++)
            if(s[i]==(s[j]^s[i]) && s[i]==(s[n]^s[j])){puts("YES");can=true;break;}
        if(!can) puts("NO");
    }
    return 0;
}