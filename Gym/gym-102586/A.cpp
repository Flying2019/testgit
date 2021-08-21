#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define ll long long
using namespace std;
typedef priority_queue<int> pq;
int a[N],b[N];
char op[N];
pq q[N];int L[N],R[N],cnt;
void merge(pq &u,pq &v){while(!v.empty()) u.push(v.top()),v.pop();}
void del(int x)
{
    merge(q[x],q[R[R[x]]]);
    merge(q[R[x]],q[R[R[R[x]]]]);
    R[R[x]]=R[R[R[R[x]]]];
    L[R[R[x]]]=R[x];
}
void check(int x)
{
    for(int _=4,y=x;_;_--,y=R[y]) if(y==R[y]) return;
    if(q[x].empty() || q[R[x]].empty()) return;
    if(q[R[x]].top()+q[R[R[x]]].top()<=0) del(x);
}
int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    scanf("%s",op+1);
    for(int i=1,j=1;i<=m;i=j)
    {
        for(;j<=m && op[i]==op[j];j++);
        if(op[i]=='B')
        {
            ++cnt;
            for(int k=i;k<j;k++) q[cnt].push(b[k]);
        }
        else
        {
            ++cnt;
            for(int k=i;k<j;k++) q[cnt].push(-b[k]);
        }
    }
    for(int i=1;i<=cnt;i++) R[i]=i+1,L[i]=i-1;
    R[cnt]=cnt;
    for(int j=1;j!=R[j];j=R[j])
        check(j);
    ll las=0;
    for(int i=1;i<=n;i++)
    {
        ll w=(a[i]+las)%1000000000;
        for(int j=1;;j=R[j])
        {
            if(q[j].top()<0 && -q[j].top()<w)
            {
                ll v=-q[j].top();
                // printf("push %d %d\n",v,w);
                q[j].pop();q[j].push(-w);
                w=v;
            }
            else if(q[j].top()>0 && q[j].top()>w)
            {
                ll v=q[j].top();
                // printf("push %d %d\n",v,w);
                q[j].pop();q[j].push(w);
                w=v;
            }
            if(j==R[j]) break;
        }
        printf("%lld ",las+=w);
        for(int j=1;j!=R[j];j=R[j]) check(j);
    }
    return 0;
}