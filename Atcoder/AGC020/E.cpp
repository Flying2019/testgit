#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<cstring>
#define mod 998244353
#define ll long long
using namespace std;
map<string,ll>f,g;
ll dfs1(string);
ll dfs2(string);
ll dfs1(string s)
{
    if(f[s]) return f[s];
    int len=s.size();
    if(!len) return f[s]=1;
    ll ans=0;
    for(int i=1;i<=len;i++)
    ans=(ans+dfs2(s.substr(0,i))*dfs1(s.substr(i,len)))%mod;
    return f[s]=ans;
}
ll dfs2(string s)
{
    if(g[s]) return g[s];
    int len=s.size();
    ll res=0;
    if(len==1) return g[s]=1+(int)(s[0]=='1');
    for(int i=1;i<=len>>1;i++)
    if(len%i==0)
    {
        string t="";
        for(int j=1,r=1;j<=i;j++,t+=(char)(r+'0'),r=1)
            for(int k=j-1;k<=len-1;k+=i) r&=s[k]-'0';
        res=(res+dfs1(t))%mod;
    }
    return g[s]=res;
}
string s;
int main()
{
    cin>>s;
    printf("%lld\n",dfs1(s));
    return 0;
}