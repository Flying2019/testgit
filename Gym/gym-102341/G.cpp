#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 21
using namespace std;
//0:II0 1:III
int f[N][1<<N];
//The first position of 0
int find_f(int x){int c=0;while(x&1) c++,x>>=1;return c;}
int get(int x,int l,int r)
{
    if(l>r || r<0) return 0;
    return x>>l&((1<<(r-l))-1);
}
void init(int n=N-1)
{
    f[0][0]=0;
    f[1][0]=1,f[1][1]=2;
    for(int i=2;i<=n;i++)
        for(int s=0;s<1<<i;s++)
        {
            int res=0;
            for(int j=0;j<i;j++) if(s>>j&1) res|=1<<f[i][s^1<<j];
            for(int j=0;j<i;j++)
            if(s>>j&1) res|=1<<(f[j][get(s,0,j)]^f[i-j-1][get(s,j+1,i)]);
            else
            {
                int t=0;
                if(j!=0) t^=f[j-1][get(s,0,j-1)]^(s>>(j-1)&1);
                if(j!=i-1) t^=f[i-j-2][get(s,j+2,i)]^(s>>(j+1)&1);
                res|=1<<t;
            }
            f[i][s]=find_f(res);
        }
}
map<string,int>mp;
int a[N+2];
int main()
{
    ios::sync_with_stdio(false);
    int t;cin>>t;
    mp[".I."]=-1;mp["I.I"]=0;mp["II."]=1;mp[".II"]=1;mp["III"]=2;
    init();
    while(t --> 0)
    {
        int n,pre=1,s=0,l=0,ans=0;
        cin>>n;memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
        {
            string s;
            cin>>s;a[i]=mp[s];
        }
        for(int i=1;i<=n+1;i++)
        if(a[i]>=0)
        {
            if((a[i+1]==-1 || a[i-1]==-1) && a[i]==2) ans^=1;
            if(a[i]==0 || a[i+1]==-1 || a[i-1]==-1){ans^=f[l][s],l=s=0;continue;}
            l++;s=s<<1|(a[i]-1);
        }
        puts(ans?"First":"Second");
    }
    return 0;
}