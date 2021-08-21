#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 2000010
#define mod 1000000007
using namespace std;
short int s[N];
int l[N],r[N][2];
int F[N+10],G[N+10],H[N+10];
int *g=G+10,*h=H+10;//g is the sum,h is the Delta
class WolfDelaymasterHard
{
    private:
    void init(int n,int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
    {
        memset(s,-1,sizeof(s));
        ll x = w0;int i=0;
        for(i=0;i<wlen;i++){
            s[x+1] = 1;				// Rewrite the x-th (0-based) character of s
            x = (x * wmul + wadd) % n;
        }
        x = o0;
        for(i=0;i<olen;i++){
            s[x+1] = 0;				// Rewrite the x-th (0-based) character of s
            x = (x * omul + oadd) % n;
        }
    }
    int get(int l,int r){return (g[r]-(l==0?0:g[l-1])+mod)%mod;}
    void set(int l,int r,int &v)
    {
        if(l>r) return;
        h[l]=(h[l]+v)%mod;h[r+1]=(h[r+1]-v+mod)%mod;
    }
    void upd(int x,int &v)
    {
        if(x) h[x]=(h[x]+h[x-1])%mod;
        h[x+1]=(h[x+1]+h[x])%mod;
        v=(v+h[x])%mod;
        g[x]=g[x+1]=((x?g[x-1]:0)+v)%mod;
    }
    int get_s(int x,int al,int ar,int bl,int br)
    /*
      b  a
    **111000
    */
    {
        if(al>ar || bl>br) return 0;
        al-=x-al;ar-=x-ar;
        al=max(al,bl);ar=min(ar,br);
        if(al>ar) return 0;
        return get(al-1,ar-1);
    }
    void set_s(int x,int &res)
    {
        int ml=r[x+1][0];ml--;
        ml+=ml-x;
        set(x+2,min(ml,r[x+1][1]-1),res);
    }
    public:
    int countWords(int n,int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
    {
        init(n,wlen,w0,wmul,wadd,olen,o0,omul,oadd);
        if(n&1) return 0;
        for(int i=1;i<=n+2;i++)
        r[i][0]=r[i][1]=n+1;
        for(int i=1;i<=n;i++)
        if(~s[i]) r[i][s[i]]=i;
        for(int i=1;i<=n;i++)
        if(s[i]==0) l[i]=i;
        for(int i=1;i<=n;i++) l[i]=max(l[i],l[i-1]);
        for(int i=n;i>=0;i--)
            for(int _=0;_<=1;_++) r[i][_]=min(r[i][_],r[i+1][_]);
        int r1=0,res=1;
        upd(0,res);set_s(0,res);
        for(int i=2;i<=n;i+=2)
        {
            if(s[i]==1) r1=i;
            else if(s[i-1]==1) r1=i-1;
            int r0=l[r1],l0=r[r1][0];
            if(r1) res=get_s(i+1,r1+1,l0,r0+1,r1);
            else res=0;
            upd(i,res);
            set_s(i,res);
        }
        return res;
    }
};
WolfDelaymasterHard C;
int main()
{
    cout<<C.countWords(
2000000,
419443,
1305303,
1761823,
1007025,
874640,
1516339,
229519,
1473199

);
    return 0;
}