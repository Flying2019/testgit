#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 21
using namespace std;
int f[1<<N][N],_2[N+2];
short c0[1<<N],c1[1<<N];//c0,c1:1x，标志 1 后第一个 0 的位置和第一个 1 的位置
int pre0(int x,int lx){return 1<<lx|x;}
int calc(int x,int y,int ly){return (x<<ly)|y;}
char s[1<<N];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    int m=1<<(n+1);
    for(int i=1;i<=n+1;i++) _2[i]=_2[i-1]<<1|1;
    memset(c0,-1,sizeof(c0));memset(c1,-1,sizeof(c1));
    for(int i=2;i<m;i++)
    {
        if(c0[i>>1]!=-1) c0[i]=c0[i>>1]+1;
        if(c1[i>>1]!=-1) c1[i]=c1[i>>1]+1;
        if((i&1) && c1[i]==-1) c1[i]=0;
        if(!(i&1) && c0[i]==-1) c0[i]=0;
    }
    for(int i=0;i<=n;i++)
    {
        scanf("%s",s);
        for(int j=0;j<1<<i;j++) if(s[j]=='1') f[calc(1,j,i)][i]++;
    }
    for(int i=n;i>0;i--)
        for(int s=1;s<m;s++)
        if(f[s][i])
        {
            int t=s>>i,u=pre0(s&_2[i],i);
            // cout<<bitset<5>(s)<<" "<<i<<" "<<bitset<5>(u)<<" : ";
            if(c0[u]!=-1)
            {
                int v=t<<(c0[u]+1)|(s&_2[c0[u]]);
                f[v][c0[u]]+=f[s][i];
                // cout<<bitset<5>(v)<<","<<c0[u]<<" ";
            }
            if(c1[u]!=-1)
            {
                int v=t<<(c1[u]+1)|(1<<c1[u])|(s&_2[c1[u]]);
                f[v][c1[u]]+=f[s][i];
                // cout<<bitset<5>(v)<<","<<c1[u]<<" ";
            }
            f[t][0]+=f[s][i];
            // cout<<" "<<f[s][i]<<endl;
        }
    int mn=m,len=0;
    for(int s=1;s<m;s++)
    if(f[s][0]>=k)
    {
        int t=-1;
        for(int i=n;i>=0;i--) if(s>>i&1){t=i;break;}
        if(t>len) len=t,mn=s;
        else if(t==len) mn=min(mn,s);
    }
    for(int i=len-1;i>=0;i--) printf("%d",mn>>i&1);
    return 0;
}