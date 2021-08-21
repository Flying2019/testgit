#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=2010,C=26,mod=998244353;
int n,m,s[N];
char str[N];
int mx[N],nxt[N],f[N][N];
int cmp(int x,int y){return s[x]>s[y]?x:y;}
int main()
{
    scanf("%d%s",&m,str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) s[i]=str[i]-'a'+1;
    if(*max_element(s,s+n)==0){puts("0");return 0;}
    for(int i=mx[0]=1;i<=n;i++)
    {
        for(nxt[i]=nxt[i-1];nxt[i] && s[nxt[i]+1]!=s[i];nxt[i]=nxt[nxt[i]]);
        if(i!=1 && s[nxt[i]+1]==s[i]) ++nxt[i];
        mx[i]=cmp(mx[nxt[i]],i+1);
    }
    f[0][0]=1;
    for(int i=0;i<m;i++)
        for(int j=0;j<=n;j++)
        if(f[i][j]) f[i+1][mx[j]]=(f[i+1][mx[j]]+f[i][j])%mod,f[i+1][0]=(f[i+1][0]+1ll*f[i][j]*(C-s[mx[j]]))%mod;
    int ans=1;
    for(int i=0;i<m;i++) ans=26ll*ans%mod;
    for(int i=0,j,u;i<=n;i++)
    {
        for(j=m,u=i;j && u;j--,u=mx[u]) ans=(ans-1ll*f[j-1][i]*(C-s[mx[u]]))%mod;
        if(!j) ans-=u==i;
        else if(!u) ans=(ans-f[j][i])%mod;
    }
    printf("%d\n",(ans%mod+mod)%mod);
    return 0;
}