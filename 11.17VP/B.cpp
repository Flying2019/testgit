#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int cnt[26][N],tt[26];
char s[N];
int tm[26];
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) cnt[s[i]-'a'][++tt[s[i]-'a']]=i;
    int m;
    scanf("%d",&m);
    while(m --> 0)
    {
        scanf("%s",s+1);
        int l=strlen(s+1),ans=0;
        memset(tm,0,sizeof(tm));
        for(int i=1;i<=l;i++) tm[s[i]-'a']++;
        for(int i=0;i<26;i++) ans=max(ans,cnt[i][tm[i]]);
        printf("%d\n",ans);
    }
    return 0;
}