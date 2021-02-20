#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define P pair<int,int>
#define MP make_pair
#define N 1000010
using namespace std;
char s[N];
int n,cnt,v[N];
string r;
vector<P >ans;
string rev(string s)
{
    reverse(s.begin(),s.end());
    for(int i=0;i<s.size();i++) s[i]=s[i]<'a'?s[i]-'A'+'a':s[i]-'a'+'A';
    return s;
}
int main()
{
    scanf("%d%s",&n,s);
    for(int i=1;i<1<<n;i++)
    if(s[i]=='1')
        for(int j=0;j<i;j++)
        if((i&j)==j && s[j]=='0'){puts("Impossible");return 0;}
    puts("Possible");
    for(int i=0;i<1<<n;i++)
    if(s[i]=='0')
    {
        bool sm=true;
        for(int j=0;j<i;j++)
        if((i&j)==j && s[j]=='0') sm=false;
        if(!sm) continue;
        r.clear();
        for(int j=0;j<n;j++)
        if((i>>j)&1)
        {
            if(r.empty()) r=('a'+j);
            else r=(char)('a'+j)+r+(char)('A'+j)+rev(r);
        }
        int p=0;
        for(char c:r)
        {
            if(c<'a')
            {
                while(p<c-'A') ans.push_back(MP(++p,0));
                while(p>c-'A') ans.push_back(MP(--p,0));
                ans.push_back(MP(p+1,0));ans.push_back(MP(p+1,1));
                ans.push_back(MP(p,1));ans.push_back(MP(p,0));
            }
            else
            {
                while(p<c-'a') ans.push_back(MP(++p,0));
                while(p>c-'a') ans.push_back(MP(--p,0));
                ans.push_back(MP(p,1));ans.push_back(MP(p+1,1));
                ans.push_back(MP(p+1,0));ans.push_back(MP(p,0));
            }
        }
        while(p) ans.push_back(MP(--p,0));
    }
    printf("%d\n",(int)ans.size());
    puts("0 0");
    for(P u:ans) printf("%d %d\n",u.first,u.second);
    return 0;
}