#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
class Crypto {
public:
    Crypto() {
        sm = cnt = 0;
        seed();
    }

    int decode(int z) {
        z ^= next();
        z ^= (next() << 8);
        z ^= (next() << 16);
        z ^= (next() << 22);
        return z;
    }

    void query(long long z) {
        const long long B = 425481007;
        const long long MD = 1000000007;
        cnt++;
        sm = ((sm * B % MD + z) % MD + MD) % MD;
        seed();
    }
private:
    long long sm;
    int cnt;

    uint8_t data[256];
    int I, J;

    void swap_data(int i, int j) {
        uint8_t tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }

    void seed() {
        uint8_t key[8];
        for (int i = 0; i < 4; i++) {
            key[i] = (sm >> (i * 8));
        }
        for (int i = 0; i < 4; i++) {
            key[i+4] = (cnt >> (i * 8));
        }

        for (int i = 0; i < 256; i++) {
            data[i] = i;
        }
        I = J = 0;

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + data[i] + key[i%8]) % 256;
            swap_data(i, j);
        }
    }

    uint8_t next() {
        I = (I+1) % 256;
        J = (J + data[I]) % 256;
        swap_data(I, J);
        return data[(data[I] + data[J]) % 256];
    }
}c;
int mod;
#define ll long long
struct F{
    #define M 500
    ll a[M];
    ll& operator [](const int b){return a[b];}
    F(void){memset(a,0xcf,sizeof(a));a[0]=0;}
    void insert(int x,int w)
    {
        x%=mod;
        static ll g[M];
        for(int i=0;i<mod;i++) g[(i+x)%mod]=a[i]+w;
        for(int i=0;i<mod;i++) a[i]=max(a[i],g[i]);
    }
}f[N],g;
int fl;
int cw[N],cv[N],cl,cr;
ll answer(F a,int l,int r){ll ans=0;for(int i=l;i<=r;i++) ans=min(ans,a[i]);return ans;}
ll answer(F &a,F &b,int l,int r)
{
    int tl=1,tr=0;ll ans=-1000000000;
    static ll g[M*3],h[M*3];
    for(int i=r;i>=l;i--)
    {
        while(tl<=tr && g[tr]<=b[i]) tr--;
        g[++tr]=b[i];h[tr]=i;
    }
    int pr=r+1,pl=l;
    for(int i=0;i<mod;i++)
    {
        if(tl<=tr) ans=max(ans,a[i]+g[tl]);
        pr=(pr-1+mod)%mod;pl=(pl-1+mod)%mod;
        while(tl<=tr && h[tl]==pr) tl++;
        while(tl<=tr && g[tr]<=b[pl]) tr--;
        g[++tr]=b[pl];h[tr]=pl;
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d%d",&mod,&n);
    for(int i=1;i<=n;i++)
    {
        int opt,w,v,l,r;
        scanf("%d%d%d%d%d",&opt,&w,&v,&l,&r);
        opt=c.decode(opt),w=c.decode(w),v=c.decode(v),l=c.decode(l),r=c.decode(r);
        if(opt==1) g.insert(w,v),cw[++cr]=w,cv[cr]=v;
        else if(opt==2)
        {
            if(fl) fl--;
            else
            {
                cl++;
                for(int i=1;i<=cr-cl;i++) f[i]=f[i-1],f[i].insert(cw[cr-i+1],cv[cr-i+1]);
                fl=cr-cl;
                cl=cr;g=F();
            }
        }
        ll ans=answer(f[fl],g,l,r);
        if(ans<0) ans=-1;
        c.query(ans);
        printf("%lld\n",ans);
    }
    return 0;
}