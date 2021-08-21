#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 1000010
#define ll long long
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
#define mod 1000000007
using namespace std;
P operator +(const P a,const P b){return MP((a.fi+b.fi)%mod,(a.se+b.se)%mod);}
P operator +(const P a,const int b){return MP((a.fi+b)%mod,(a.se+b)%mod);}
P operator -(const P a,const P b){return MP((a.fi-b.fi+mod)%mod,(a.se-b.se+mod)%mod);}
P operator *(const P a,const P b){return MP(1ll*a.fi*b.fi%mod,1ll*a.se*b.se%mod);}
P operator *(const P a,const int b){return MP(1ll*a.fi*b%mod,1ll*a.se*b%mod);}
const P base=MP(2333333,23333333);
string S[N];
P h[N],b[N],t[N];
int s[N];
P fl[N],fr[N];
P get(int l,int r){return fl[r]-fl[l-1]*b[r-l+1];}
P getr(int l,int r){return fr[l]-fr[r+1]*b[r-l+1];}
ll solve(int n)
{
    memset(s,0,sizeof(s));
    sort(t+1,t+n+1);
    int q=unique(t+1,t+n+1)-t-1;
    for(int i=1;i<=n;i++) s[i]=lower_bound(t+1,t+q+1,h[i])-t;
    vector<int>left,right;
    memset(h,0,sizeof(h));memset(fl,0,sizeof(fl));memset(fr,0,sizeof(fr));
    for(int i=1;i<=n;i++) fl[i]=fl[i-1]*base+s[i];
    for(int i=n;i;i--) fr[i]=fr[i+1]*base+s[i];
    int p=0;left.push_back(p);
    for(int i=2;i<=n;i++) if((i-p)%2==0 && get(p+1,i)==getr(p+1,i))
        left.push_back((p+i)/2),p=(p+i)/2,i=p;
    p=n+1;right.push_back(n+1);
    for(int i=n;i;i--) if((p-i)%2==0 && get(i,p-1)==getr(i,p-1))
        right.push_back((p+i)/2),p=(p+i)/2,i=p;
    // for(int u:left) printf("%d ",u);puts("");
    // for(int u:right) printf("%d ",u);puts("");
    ll ans=0;
    reverse(left.begin(),left.end());
    for(int i=0,j=0;i<left.size();i++)
    {
        while(j<right.size() && right[j]>left[i]+1) j++;
        ans+=j;
    }
    return ans;
}
int main()
{
    b[0]=MP(1,1);
    for(int i=1;i<=N-10;i++) b[i]=b[i-1]*base;
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>S[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) h[i+1]=h[i+1]*base+(S[i][j]-'a'+1),t[i+1]=h[i+1];
    ll ans=solve(n);
    memset(h,0,sizeof(h));memset(t,0,sizeof(t));
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++) h[i+1]=h[i+1]*base+(S[j][i]-'a'+1),t[i+1]=h[i+1];
    ans*=solve(m);
    printf("%lld\n",ans);
    return 0;
}