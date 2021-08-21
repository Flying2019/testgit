#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
#define M 32
using namespace std;
char ans[M];
int s[M];
int main()
{
    int n,m,l,r,T=0;
    while(cin>>n>>m>>l>>r)
    {
        printf("Case %d:\n",++T);
        s[0]=1;int tt=1;
        for(int i=1;i<=r;i++)
        {
            if(i>=l)
            {
                for(int i=0;i<tt;i++) ans[i]='a'+s[i]-1;ans[tt]='\0';
                printf("%s\n",ans);
            }
            if(tt==n)
            {
                while(s[tt-1]==m) tt--;
                s[tt-1]++;continue;
            }
            for(int i=tt;i<n;i++) s[i]=s[i%tt];
            tt=n;
            while(s[tt-1]==m) tt--;
            s[tt-1]++;
        }
    }
    return 0;
}