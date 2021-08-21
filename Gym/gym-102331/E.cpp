#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>
#include<algorithm>
#define N 128
#define M 200010
using namespace std;
typedef bitset<N> bit;
typedef long long ll;
bit b[N];int id[N];ll w[M],ans;
void insert(bit u,int p)
{
    for(int i=N-1;~i;i--)
    if(u.test(i))
    {
        if(id[i])
        {
            if(w[id[i]]<w[p]) swap(id[i],p),swap(u,b[i]);
            u^=b[i];
        }
        else{id[i]=p;b[i]=u;return;}
    }
    ans-=w[p];
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;ll a;
        scanf("%d%d%lld%d",&u,&v,&a,&w[i]);
        u+=59,v+=59;
        bit p(a);
        p.set(u);p.set(v);
        ans+=w[i];
        insert(p,i);
        printf("%lld\n",ans);
    }
    return 0;
}