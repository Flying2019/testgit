#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
char s[N],t[N];
int main()
{
    int q;
    scanf("%d",&q);
    while(q --> 0)
    {
        scanf("%s%s",s+1,t+1);
        int n=strlen(s+1),m=strlen(t+1);
        bool rt=false;
        for(int i=1;i<=n;i++)
        if(s[i]==t[1])
        {
            // printf("%d:",i);
            for(int j=1;j<=min(n-i+1,m);j++)
            if(s[i+j-1]==t[j])
            {
                bool can=true;
                for(int k=1;j+k<=m;k++)
                {
                    if(i+j-1-k<=0){can=false;break;}
                    if(s[i+j-1-k]!=t[j+k]){can=false;break;}
                }
                if(can){rt=true;break;}
            }
        }
        puts(rt?"Yes":"No");
    }
    return 0;
}