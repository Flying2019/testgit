#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define N 200010
#define MP make_pair
#define fi first
#define se second
#define mod 1000000007
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
P operator +(const P a,const P b){return MP((a.fi+b.fi)%mod,(a.se+b.se)%mod);}
P operator +(const P a,const int b){return MP((a.fi+b)%mod,(a.se+b)%mod);}
P operator -(const P a,const P b){return MP((a.fi-b.fi+mod)%mod,(a.se-b.se+mod)%mod);}
P operator *(const P a,const P b){return MP(1ll*a.fi*b.fi%mod,1ll*a.se*b.se%mod);}
const P B=MP(233,2333);
P hs[N],bs[N],d[N];
int ch[N][27];
map<P,int>st;
void init(int n=N-10)
{
    bs[0]=MP(1,1);
    for(int i=1;i<=n;i++) bs[i]=bs[i-1]*B;
}
void dfs(int u)
{
    st[d[u]]=u;
    for(int i=1;i<=26;i++)
    if(ch[u][i])
    {
        d[ch[u][i]]=d[u]*B+i;
        dfs(ch[u][i]);
    }
}
char s[N];
P get(int l,int r){return hs[r]-hs[l-1]*bs[r-l+1];}
int f[N][21];
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
        {
            char op[3];int u;
            scanf("%d%s",&u,op);
            ch[u][op[0]-'a'+1]=i;
        }
        dfs(0);
        scanf("%s",s+1);
        for(int i=1;i<=m;i++) hs[i]=hs[i-1]*B+(s[i]-'a'+1);
        for(int i=1;i<=m;i++)
        {
            int l=i,r=m;f[i][0]=m+1;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(st.count(get(i,mid))) l=mid+1;
                else r=mid-1,f[i][0]=mid;
            }
        }
        f[m+1][0]=m+1;
        for(int p=1;p<=20;p++)
            for(int i=1;i<=m+1;i++) f[i][p]=f[min(f[i][p-1],m)+1][p-1];
        while(k --> 0)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            int t=0;
            for(int i=20;i>=0;i--)
            if(f[l][i]<=r) l=f[l][i]+1,t+=1<<i;
            if(f[l][0]<=r) l=f[l][0]+1,t++;
            int rt=0;
            if(l<=r) rt=st[get(l,r)];
            printf("%d %d\n",t,rt);
        }
        st.clear();
        for(int i=0;i<=n;i++) memset(ch[i],0,sizeof(ch[i]));
    }
    return 0;
}