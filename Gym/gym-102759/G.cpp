#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=100010,M=5,MX=625,mod=1000000007;
typedef vector<int> vec;
char s[N];
int n,k;
vec u(4),v(4);
void get(int x){for(register int i=0;i<=3;x/=M,i++) u[i]=x%M;}
int id(){int x=0;for(register int i=3;i>=0;i--) x=x*5+v[i];return x;}
bool check(){return u[k]<=k;}
int f[MX],g[MX],fail[N][26];
void init()
{
    v={0,1,2,3};
    f[id()]=1;
    for(int i=1;i<=n;i++)
    {
        memcpy(g,f,sizeof(f));memset(f,0,sizeof(f));
        for(int j=0;j<MX;j++) if(g[j])
        {
            get(j);
            for(int c=0;c<26;c++)
            {
                v={4,u[0],u[1],u[2]};
                for(int p=0;p<4;p++) v[p]=min(v[p],u[p]+fail[i-p+u[p]][c]);
                (f[id()]+=g[j])%=mod;
            }
        }
    }
}
int main()
{
    scanf("%s%d",s+1,&k);
    n=strlen(s+1);
    for(int i=n;i;i--)
        for(int j=0;j<26;j++) if(j!=s[i]-'A') fail[i][j]=fail[i+1][j]+1;
    init();
    int ans=0;
    for(int i=0;i<MX;i++)
    if(f[i]){get(i);if(check()) ans=(ans+f[i])%mod;}
    printf("%d\n",ans);
    return 0;
}