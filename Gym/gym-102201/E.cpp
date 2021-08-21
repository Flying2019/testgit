#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 500010
#define ll long long
using namespace std;
const ll inf=1000000000000;
struct node{
    int u;ll w;
    node(int U=0,ll W=0):u(U),w(W){}
    bool operator <(const node a)const{return w>a.w;}
};
typedef priority_queue<node> pq;
pq ql,qr,pl,pr;
ll a[N],b[N],c[N];
void pop(pq &a,int o)
{
    while(!a.empty())
    {
        node v=a.top();
        if(o!=c[v.u]) a.pop();
        else break;
    }
}
ll W1()
{
    if(ql.empty() || qr.empty()) return inf;
    node l=ql.top(),r=qr.top();
    if(l.u!=r.u) return l.w+r.w;
    ql.pop();qr.pop();
    pop(ql,0);pop(qr,0);
    if(ql.empty() && qr.empty()){ql.push(l);qr.push(r);return inf;}
    ll w=0;
    if(ql.empty()) w=l.w+qr.top().w;
    else if(qr.empty()) w=r.w+ql.top().w;
    else w=min(l.w+qr.top().w,r.w+ql.top().w);
    ql.push(l);qr.push(r);
    return w;
}
ll W2()
{
    if(ql.size()<2 || pl.empty()) return inf;
    node l1=ql.top();ql.pop();pop(ql,0);
    if(ql.empty()){ql.push(l1);return inf;}
    ll w=l1.w+ql.top().w+pl.top().w;ql.push(l1);
    return w;
}
ll W3()
{
    if(qr.size()<2 || pr.empty()) return inf;
    node r1=qr.top();qr.pop();pop(qr,0);
    if(qr.empty()){qr.push(r1);return inf;}
    ll w=r1.w+qr.top().w+pr.top().w;qr.push(r1);
    return w;
}
ll ans=0;
void pushl(int u){c[u]=1;pl.push(node(u,b[u]-a[u]));}
void pushr(int u){c[u]=2;pr.push(node(u,a[u]-b[u]));}
void D1()
{
    pop(ql,0);pop(qr,0);
    node l=ql.top(),r=qr.top();ql.pop();qr.pop();
    pop(ql,0);pop(qr,0);
    if(l.u!=r.u){if(c[l.u] || c[r.u]) throw;pushl(l.u);pushr(r.u);return;}
    if(l.w+qr.top().w<r.w+ql.top().w)
    {
        node tr=qr.top();qr.pop();qr.push(r);
        if(c[l.u] || c[tr.u]) throw;
        pushl(l.u);pushr(tr.u);return;
    }
    node tl=ql.top();ql.pop();ql.push(l);
    if(c[tl.u] || c[r.u]) throw;
    pushl(tl.u);pushr(r.u);return;
}
void D2()
{
    node l1=ql.top();ql.pop();
    pop(ql,0);
    node l2=ql.top();ql.pop();
    node t=pl.top();pl.pop();
    pop(ql,0);
    if(c[l1.u] || c[l2.u]) throw;
    pushl(l1.u);pushl(l2.u);pushr(t.u);
}
void D3()
{
    node r1=qr.top();qr.pop();
    pop(qr,0);
    node r2=qr.top();qr.pop();
    pop(qr,0);
    node t=pr.top();pr.pop();
    if(c[r1.u] || c[r2.u]) throw;
    pushr(r1.u);pushr(r2.u);pushl(t.u);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) scanf("%lld%lld",&a[i],&b[i]),ql.push(node(i,a[i])),qr.push(node(i,b[i]));
    for(int i=1;i<=n;i++)
    {
        pop(ql,0);pop(qr,0);pop(pl,1);pop(pr,2);
        ll w1=W1(),w2=W2(),w3=W3();
        if(w1<=w2 && w1<=w3) ans+=w1,D1();
        else if(w2<=w3 && w2<=w1) ans+=w2,D2();
        else ans+=w3,D3();
        printf("%lld\n",ans);
    }
    return 0;
}