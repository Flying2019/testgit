#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
char s[N];
int main()
{
    int n;
    scanf("%d",&n);
    int c1=0,c2=0,c3=0,c4=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        int m=strlen(s+1);
        for(int i=1;i<m;i++)
        if(s[i]=='A' && s[i+1]=='B') c1++;
        if(s[1]=='B' && s[m]=='A'){c4++;continue;}
        if(s[1]=='B') c2++;
        if(s[m]=='A') c3++;
    }
    int res=c1;
    if(c4)
    {
        c4--;
        if(c2 || c3) c2--,c3--,res+=2;
    }
    res+=min(c2,c3)+c4;
    printf("%d\n",res);
    return 0;
}