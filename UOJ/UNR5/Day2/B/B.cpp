#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
typedef __uint128_t u128;
inline u128 read() {
    static char buf[100];
    scanf("%s", buf);
    // std::cin >> buf;
    u128 res = 0;
    for(int i = 0;buf[i];++i) {
        res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
    }
    return res;
}
inline void write(u128 res) {
    if(res >= 16)
        write(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
    //std::cout.put(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}
u128 a[N],_2[128];
struct bas{
    int b[128];
    u128 hav,ans;
    void init(u128 a)
    {
        memset(b,0,sizeof(b));hav=0;ans=a;
        for(int i=0;a;a>>=1,i++) if(a&1) b[i]++,hav|=_2[i];
    }
}val[N<<2];
u128 tag[N<<2];
bas operator+(const bas a,const bas b)
{
    bas c=a;
    for(int i=0;i<128;i++) c.b[i]+=b.b[i];
    c.hav|=b.hav;c.ans+=b.ans;
    return c;
}
void setg(int u,u128 v)
{
    tag[u]|=v;
    for(int i=0;i<128;i++) if(v>>i&1 && val[u].b[i]) val[u].ans-=val[u].b[i]*_2[i],val[u].b[i]=0,val[u].hav^=_2[i];
}
void push(int u){if(!tag[u]) return;setg(u<<1,tag[u]);setg(u<<1|1,tag[u]);tag[u]=0;}
void build(int u,int l,int r)
{
    if(l==r){val[u].init(a[l]);return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    val[u]=val[u<<1]+val[u<<1|1];
}
void insert(int u,int l,int r,int L,int R,u128 v)
{
    if(!(val[u].hav&v)) return;
    if(L<=l && r<=R){setg(u,v);return;}
    int mid=(l+r)>>1;push(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    val[u]=val[u<<1]+val[u<<1|1];
}
void insert_brute(int u,int l,int r,int L,int R,u128 v)
{
    if(!val[u].hav) return;
    if(l==r)
    {
        tag[u]=0;
        val[u].init(val[u].ans/v);
        return;
    }
    int mid=(l+r)>>1;push(u);
    if(L<=mid && val[u<<1].hav) insert_brute(u<<1,l,mid,L,R,v);
    if(R>mid && val[u<<1|1].hav) insert_brute(u<<1|1,mid+1,r,L,R,v);
    val[u]=val[u<<1]+val[u<<1|1];
}
u128 answer(int u,int l,int r,int L,int R)
{
    if(!val[u].hav) return 0;
    if(L<=l && r<=R) return val[u].ans;
    int mid=(l+r)>>1;push(u);
    if(R<=mid) return answer(u<<1,l,mid,L,R);
    if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
    return answer(u<<1,l,mid,L,R)+answer(u<<1|1,mid+1,r,L,R);
}
int main()
{
    _2[0]=1;
    for(int i=1;i<128;i++) _2[i]=_2[i-1]<<1;
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) a[i]=read();
    build(1,1,n);
    while(q --> 0)
    {
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if(op==3){write(answer(1,1,n,l,r));puts("");continue;}
        u128 v=read();
        if(op==1){if(v>1) insert_brute(1,1,n,l,r,v);}
        else insert(1,1,n,l,r,~v);
    }
    return 0;
}