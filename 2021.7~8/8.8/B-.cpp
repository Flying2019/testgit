#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n;
const int MAXN=8e3+7;
int a[MAXN];
void lsh(){
    vector<int> vec;
    vec.push_back(-1);
    for(ri i=1;i<=n;++i)  vec.push_back(a[i]);
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(ri i=1;i<=n;++i) a[i]=lower_bound(vec.begin(),vec.end(),a[i])-vec.begin();
}
struct SegT
{
    struct T
    {
        int cnt[2],tag;
    }t[MAXN<<2];
    #define lc u<<1
    #define rc u<<1|1
    #define mid (L+R>>1)
    void pushr(int u){
        t[u].tag^=1,swap(t[u].cnt[0],t[u].cnt[1]);
    }
    void update(int u){
        t[u].cnt[0]=t[lc].cnt[0]+t[rc].cnt[0];
        t[u].cnt[1]=t[lc].cnt[1]+t[rc].cnt[1];
    }
    void pushdown(int u){
        if(t[u].tag){
            pushr(lc),pushr(rc);
            t[u].tag=0;
        }
    }
    int query(int u,int l,int r,int L=1,int R=n){
        if(l==L&&r==R) return t[u].cnt[0]+t[u].cnt[1];
        pushdown(u);
        if(r<=mid) return query(lc,l,r,L,mid);
        else if(l>mid) return query(rc,l,r,mid+1,R);
        else return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
    }
    void insert(int u,int pos,int w,int L=1,int R=n){
        if(L==R){
            t[u].cnt[w]++;
            return;
        }
        pushdown(u);
        if(pos<=mid) insert(lc,pos,w,L,mid);
        else insert(rc,pos,w,mid+1,R);
        update(u);
    }
    void modify(int u,int l,int r,int L=1,int R=n){
        if(!(t[u].cnt[0]+t[u].cnt[1])) return;
        if(l==L&&r==R) return pushr(u);
        pushdown(u);
        if(r<=mid) modify(lc,l,r,L,mid);
        else if(l>mid) modify(rc,l,r,mid+1,R);
        else modify(lc,l,mid,L,mid),modify(rc,mid+1,r,mid+1,R);
        update(u);
    }
    void clear(){
        for(ri i=1;i<=4*n;++i) t[i].cnt[0]=t[i].cnt[1]=t[i].tag=0;
    }
    #undef lc
    #undef rc
    #undef mid
}T;
int fa[MAXN],mn[MAXN];
int find(int k){return fa[k]==k?k:fa[k]=find(fa[k]);}
#define pii pair<int,int>
void merge(int u,int v){
    u=find(u),v=find(v);
    // s.erase((pii){mn[u],u}),s.erase((pii){mn[v],v});
    if(u==v) return;
    if(mn[u]>mn[v]) swap(u,v);
    fa[v]=u;
    // s.insert((pii){mn[u],u});
}
set<pii> rs,s;
int ans;
/*
1 3
1 4
3 4
3 6
4 6
6 7
*/
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    n=read();
    for(ri i=1;i<=n;++i) a[i]=read();
    lsh();
    for(ri l=1;l<=n;++l){
        T.clear();
        s.clear();
        rs.clear();
        // if(l==56)
        //     puts("fuck");
        for(ri r=l;r<=n;++r){
            // if(l==56&&r==60){
            //     puts("fuck");
            // }
            fa[r]=r,mn[r]=a[r];
            T.insert(1,a[r],(a[r]==1?0:T.query(1,1,a[r]-1))&1);
            if(a[r]!=1) T.modify(1,1,a[r]-1);
            int cnt=0;
            for(auto it=s.begin();it!=s.end();){
                if(it->first>=a[r]) break;
                ++cnt;
                merge(r,it->second);
                auto res=it;++it;
                s.erase(res);
            }
            for(auto it=rs.begin();it!=rs.end();){
                if(it->first>=a[r]) break;
                ++cnt;
                merge(r,it->second);
                auto res=it;++it;
                rs.erase(res);
            }
            if(cnt){
                int u=find(r);
                s.insert((pii){mn[u],u});
            }
            else{
                int u=find(r);
                rs.insert((pii){mn[u],u});
            }
            if(s.size()<=1&&!T.t[1].cnt[1]){
                printf("%d %d\n",l,r);
                ++ans;
            }
        }
    }
    print(ans);
    // fprintf(stderr,"%lf",1000.0*clock()/CLOCKS_PER_SEC);
    return 0;
}