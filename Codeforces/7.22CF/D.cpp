#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
char s[N],t[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T --> 0)
    {
        scanf("%s%s",s+1,t+1);
        int n=strlen(s+1),m=strlen(t+1);
        if(n<m){puts("NO");continue;}
        bool can=false;
        for(int _=1;_<=2;_++)
        {
            if(_==2 && n==m) break;
            int j=1;
            for(int i=_;i<=n && j<=m;)
            if(s[i]==t[j]) i++,j++;
            else i+=2;
            if(j>m) can=true;
        }
        puts(can?"Yes":"No");
    }
    return 0;
}