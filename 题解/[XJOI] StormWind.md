### [����](http://115.236.49.52:83/contest/1585/problem/2)
����DAG���·���ʾ���һ����������Ϊ�˷��㣬���ǿ��Խ�һ������Դ�� $S$ �ͻ�� $T$�����Է��֣����ڱ��뾭��һ���� $u$���𰸾��� $S\rightarrow u$ ���·���� $u\rightarrow T$ ���·�����뾭��ĳһ����ͬ��

������δ������1 ��������ǰ����е㰴���������򣬿��Է������б߶���������ӵġ����ڲ�����ĳһ�㣬һ������һ���߿�Խ����㡣���仰˵����Խ�����ı����ҽ���һ��������ĳһ�·�

���Զ��� $l\rightarrow r$ �ıߣ�ֱ�Ӷ� $(l,r)$ ���߶��������޸�/ȡ $\max$ ���ɡ����Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define vi vector<int>::iterator
#define N 400010
#define ll long long
using namespace std;
vector<int>rd[N],rs[N];
int id[N],nid[N],pre[N],suf[N],n;
int deg[N],cnt;
queue<int>q;
void topo(int s,int t,vector<int> r[],vector<int> rf[],int dis[])
{
    cnt=0;
    for(int i=1;i<=n;i++) dis[i]=-1,deg[i]=rf[i].size();
    q.push(s);
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        id[++cnt]=u;
        nid[u]=cnt;
        q.pop();
        for(vi i=r[u].begin();i!=r[u].end();i++)
        {
            int v=*i;
            deg[v]--;
            dis[v]=max(dis[v],dis[u]+1);
            if(!deg[v]) q.push(v);
        }
    }
}
int val[N<<1],tag[N<<1];
inline void set_tag(int u,int v){tag[u]=max(tag[u],v);val[u]=max(val[u],v);}
void push_down(int u){set_tag(u<<1,tag[u]);set_tag(u<<1|1,tag[u]);tag[u]=0;}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(R<L) return;
    if(L<=l && r<=R){set_tag(u,v);return;}
    push_down(u);
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    val[u]=max(val[u<<1],val[u<<1|1]);
}
int answer(int u,int l,int r,int p)
{
    if(l==r) return val[u];
    push_down(u);
    int mid=(l+r)>>1;
    if(p<=mid) return answer(u<<1,l,mid,p);
    else return answer(u<<1|1,mid+1,r,p);
}
int x[N],y[N];
int main()
{
    int m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        rd[x[i]].push_back(y[i]);
        rs[y[i]].push_back(x[i]);
    }
    for(int i=1;i<=n;i++) rs[i].push_back(n+1),rd[n+1].push_back(i),x[++m]=n+1,y[m]=i;
    for(int i=1;i<=n;i++) rd[i].push_back(n+2),rs[n+2].push_back(i),x[++m]=i,y[m]=n+2;
    int s=n+1,t=n+2;
    n+=2;
    topo(t,s,rs,rd,suf);
    topo(s,t,rd,rs,pre);
    for(int i=1;i<=m;i++) insert(1,1,n,nid[x[i]]+1,nid[y[i]]-1,pre[x[i]]+suf[y[i]]+1);
    for(int i=1;i<=q;i++)
    {
        int opt,u;
        scanf("%d%d",&opt,&u);
        if(opt==1) printf("%d\n",max(answer(1,1,n,nid[u])-2,0));
        else if(opt==2) printf("%d\n",max(pre[u]+suf[u]-2,0));
        else printf("%d\n",max(pre[x[u]]+suf[y[u]]+1-2,0));
    }
    return 0;
}
```
