#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 1000010
#define ull unsigned long long
#define B 2333
using namespace std;
char str[N];
int s[N],n;
ull h[N],bs[N];
ull get(int l,int r){return h[r]-h[l-1]*bs[r-l+1];}
int lcp(int x,int y)
{
    int l=1,r=n-max(x,y)+1,res=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(get(x,x+mid-1)==get(y,y+mid-1)) l=mid+1,res=mid;
        else r=mid-1;
    }
    return res;
}
int lcs(int x,int y)
{
    int l=1,r=min(x,y),res=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid+1,res=mid;
        else r=mid-1;
    }
    return res;
}
bool cmp(int l1,int r1,int l2,int r2)//s[l1:r1]<s[l2:r2]
{
    int l=lcp(l1,l2);
    if(l>min(r1-l1,r2-l2)) return r1-l1<r2-l2;
    return s[l1+l]<s[l2+l];
}
struct runs{
    int i,j,p;
    runs(int i=0,int j=0,int p=0):i(i),j(j),p(p){}
    bool operator ==(const runs a)const{return i==a.i && j==a.j && p==a.p;}
    bool operator <(const runs a)const{return i==a.i?j<a.j:i<a.i;}
};
vector<runs>ans;
int st[N],t,run[N];
void lyndon()
{
    t=0;
    for(int i=n;i;i--)
    {
        st[++t]=i;
        for(;t>1 && cmp(i,st[t],st[t]+1,st[t-1]);t--);
        run[i]=st[t];
    }
}
void init()
{
    bs[0]=1;
    for(int i=1;i<=n;i++) h[i]=h[i-1]*B+s[i],bs[i]=bs[i-1]*B;
}
void get_runs()
{
    for(int i=1;i<=n;i++)
    {
        int l1=i,r1=run[i],l2=l1-lcs(l1-1,r1),r2=r1+lcp(l1,r1+1);
        if(r2-l2+1>=(r1-l1+1)*2) ans.push_back(runs(l2,r2,r1-l1+1));
    }
}
int main()
{
    // freopen("runs1.in","r",stdin);
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) s[i]=str[i]-'a'+1;
    init();
    lyndon();
    get_runs();
    for(int i=1;i<=n;i++) s[i]=27-s[i];
    lyndon();
    get_runs();
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto u:ans) printf("%d %d %d\n",u.i,u.j,u.p);
    return 0;
}