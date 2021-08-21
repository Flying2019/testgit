#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
typedef long long ll;
typedef unsigned un;
typedef std::pair<int,int> pii;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();return f*x;}
ll max(ll a,ll b){return a>b?a:b;}
ll min(ll a,ll b){return a<b?a:b;}
template <typename T> bool umax(T& a,T t){if(t>a)return a=t,1;return 0;}
template <typename T> bool umin(T& a,T t){if(t<a)return a=t,1;return 0;}
/**********/
const int MAXN = 200011,mod1 = 1e9+93,mod2 = 1e9+97,P = 1e9+7;
inline int D1(int x){return x<0?x+mod1:x;}
inline int D2(int x){return x<0?x+mod2:x;}
ll pw1[MAXN],pw2[MAXN];
int f1[MAXN],f2[MAXN],rf1[MAXN],rf2[MAXN];
int get1(int l,int r){return D1(f1[r]-f1[l-1]*pw1[r-l+1]%mod1);}
int get2(int l,int r){return D2(f2[r]-f2[l-1]*pw2[r-l+1]%mod2);}
int n;
char a[MAXN];
int LCP(int x,int y)
{
    if(a[x]!=a[y])return 0;
    //printf("LCP x=%d,y=%d\n",x,y);
    un l=1,r=min(n-x+1,n-y+1);
    while(l<r)
    {
        un mid=(l+r+1)>>1;
        if(get1(x,x+mid-1)==get1(y,y+mid-1)&&get2(x,x+mid-1)==get2(y,y+mid-1))l=mid;
        else r=mid-1;
    }
    return l;
}
int LCS(int x,int y)
{
    if(a[x]!=a[y])return 0;
    un l=1,r=min(x,y);
    while(l<r)
    {
        un mid=(l+r+1)>>1;
        if(get1(x-mid+1,x)==get1(y-mid+1,y)&&get2(x-mid+1,x)==get2(y-mid+1,y))l=mid;
        else r=mid-1;
    }
    return l;
}
bool Less(int l1,int r1,int l2,int r2)
{
    if(l1==l2)return r1<r2;
    //printf("l1=%d,l2=%d\n",l1,l2);
    int k=LCP(l1,l2);
    if(k>=min(r1-l1+1,r2-l2+1))return r1-l1<r2-l2;
    return a[l1+k]<a[l2+k];
}
struct Run
{
    int l,r,p;
    Run()=default;
    Run(int l,int r,int p):l(l),r(r),p(p) {}
    bool operator< (const Run& you)const{return l<you.l||(l==you.l&&r<you.r);}
    bool operator ==(const Run& you)const{return l==you.l&&r==you.r;}
}res[MAXN<<1|1];
int tot=0,s[MAXN],f[MAXN];

void Lyndon(int n)
{
    //puts("Lyndon:");
    int top=0;
    for(int i=n;i;--i)
    {
        s[++top]=i;
        while(top>1&&Less(i,s[top],s[top]+1,s[top-1]))--top;
        f[i]=s[top];
        //printf("f[%d]=%d\n",i,f[i]);
    }
}
void Get_runs()
{
    Lyndon(n);
    for(int i=1;i<=n;++i)
    {
        int l1=i,r1=f[i],l2=l1-LCS(l1-1,r1),r2=r1+LCP(l1,r1+1);
        if((r2-l2+1)>=2*(r1-l1+1))res[++tot]=Run(l2,r2,r1-l1+1);
    }
    for(int i=1;i<=n;++i)a[i]='z'-(a[i]-'a');
    Lyndon(n);
    for(int i=1;i<=n;++i)
    {
        int l1=i,r1=f[i],l2=l1-LCS(l1-1,r1),r2=r1+LCP(l1,r1+1);
        if((r2-l2+1)>=2*(r1-l1+1))res[++tot]=Run(l2,r2,r1-l1+1);
    }
    std::sort(res+1,res+tot+1),tot=std::unique(res+1,res+tot+1)-res-1;
}
std::vector<int>per[MAXN];
int dp[MAXN];
std::vector<pii>run_s[MAXN];
void solve()
{
    tot=0;
    scanf("%s",a+1);
    n=strlen(a+1);
    pw1[0]=pw2[0]=1;
    for(int i=1;i<=n;++i)pw1[i]=pw1[i-1]*233%mod1,pw2[i]=pw2[i-1]*233%mod2;
    for(int i=1;i<=n;++i)f1[i]=(f1[i-1]*233ll+a[i])%mod1,f2[i]=(f2[i-1]*233ll+a[i])%mod2;
    for(int i=n;i;--i)rf1[i]=(rf1[i+1]*233ll+a[i])%mod1,rf2[i]=(rf2[i+1]*233ll+a[i])%mod2;
    Get_runs();
    for(int i=1;i<=n;++i)per[i].clear();
    for(int i=1;i<=tot;++i)
    {
        int l=res[i].l,r=res[i].r,p=res[i].p;
        for(int s=0;s<p;++s)
            for(int j=l+s+p+p-1;j<=r;j+=p)per[j].push_back(i);
        run_s[i].clear(), run_s[i].resize(p);
    }
    int sig=1,tot=1;
    dp[0]=1;
    for(int i=1;i<=n;++i)
    {
        dp[i]=(tot)%P;
        for(auto x:per[i])
        {
            int p=res[x].p;
            int &s1=run_s[x][(i-res[x].l)%p].first,&s2=run_s[x][(i-res[x].l)%p].second;
            s1=(s1+ll(dp[i-res[x].p*2]))%P;
            s2=(s2-ll(s1)*(res[x].p))%P;
            dp[i]=(dp[i]+s2)%P;
        }
        sig=(dp[i]+sig)%P,tot=(tot+sig)%P;
    }
    printf("%d\n",(dp[n]+P)%P);
}
int main()
{
    int task=read();
    while(task--)solve();
    return 0;
}