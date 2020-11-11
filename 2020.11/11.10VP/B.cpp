#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define M 1010
using namespace std;
char s[N][M];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m,x,y;
        scanf("%d%d%d%d",&n,&m,&x,&y);
        for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
        long long ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            if(s[i][j]=='.')
            {
                if(j<m && s[i][j+1]=='.'){j++,ans+=min(2*x,y);}
                else ans+=x;
            }
        printf("%lld\n",ans);
    }
    return 0;
}