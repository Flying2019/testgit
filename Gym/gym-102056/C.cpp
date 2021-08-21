#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
using namespace std;
typedef long long ll;
const int N=100010;
int p[N],pt;bool pr[N];
const int chp[]={2*2,3*3,5*5,7*7,11*11,13*13},M=(2*3*5*7*11*13)*(2*3*5*7*11*13);
ll chw[6];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return;}
    exgcd(b,a%b,y,x);
    y-=x*(a/b);
}
void pre_work(int n=N-10)
{
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++pt]=i;
        for(int j=1;j<=pt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0) break;
        }
    }
    for(int i=0;i<6;i++)
    {
        ll x=0,y=0;
        exgcd(M/chp[i],chp[i],x,y);
        chw[i]=1ll*(M/chp[i])*((x+chp[i])%chp[i]);
    }
}
const int S=200;
int mn=1e9;
char s[S+2];
void check(int x)
{
    for(int i=0;i<200;i++)
    {
        bool t=true;
        for(int j=1;1ll*p[j]*p[j]<=x+i;j++)
        if((x+i)%(p[j]*p[j])==0){t=false;break;}
        if(s[i]-'0'!=t) return;
    }
    mn=min(mn,x);
    return;
}
vector<int>avail[6];
void dfs(int u,ll v)
{
    if(u==6)
    {
        for(int i=v%M;i+199<=1000000000;i+=M) check(i);
        return;
    }
    for(int i=0;i<avail[u].size();i++)
        dfs(u+1,v+chw[u]*avail[u][i]);
}
int main()
{
    pre_work();
    for(int i=0;i<10;i++) scanf("%s",s+(i*20));
    int c=0;
    for(int i=0;i<200;i++) c+=s[i]=='1';
    if(c<100){puts("-1");return 0;}
    for(int i=0;i<6;i++)
        for(int j=0;j<chp[i];j++)
        {
            bool can=true;
            for(int k=j;k<200;k+=chp[i]) if(s[k]=='1'){can=false;break;}
            if(can) avail[i].push_back((chp[i]-j)%chp[i]);
        }
    dfs(0,0);
    printf("%d\n",mn>=1e9?-1:mn);
    return 0;
}