### [����](http://acm.hdu.edu.cn/showproblem.php?pid=4725)
### ��Ŀ����
���� $n$ ���������ͼ��ÿ������һ������ $c_i$�����������Ĳ������1����ô��������֮����һ������Ϊ $C$ �ıߡ�

����֮�⻹�� $m$ ������ߣ��� $1\rightarrow n$ �����·��
### ���
��Ȼ�����·������ֱ��������Ȼ��ҡ�

��������һ����·����Ȼ���б߶��� $C$�����ǲ����涨һ���ڵ� $u+n$ ��ʾ $u$ ��һ������н����ıߣ�����Ϊ $C$��Ȼ��õ������� $u$ ��ĵ���һ������Ϊ0�ıߡ���ʾ��ߡ�

ע����Щ���ǵ���ġ������ͷ�ֹͬһ���ڵĵ㻥��ת�ơ�

ֱ�������·���ɡ����Ӷ� $O(m\log n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define M 800010
#define ll long long
using namespace std;
int nxt[M],to[M],w[M],head[N],cnt;
void add(int u,int v,int w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
struct node{
    int u;
    ll w;
    node(int U=0,int W=0):u(U),w(W){}
    bool operator <(const node a)const{return w>a.w;}
};
ll dis[N];
bool vis[N];
priority_queue<node>q;
ll dij(int s,int t)
{
    memset(dis,60,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    q.push(node(s,dis[s]));
    while(!q.empty())
    {
        int u=q.top().u;
        q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(!vis[v] && dis[v]>dis[u]+w[i])
            {
                dis[v]=dis[u]+w[i];
                q.push(node(v,dis[v]));
            }
        }
    }
    return dis[t];
}
int have[N],l[N];
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        memset(have,0,sizeof(have));
        memset(head,0,sizeof(head));
        cnt=0;
        int n,m,c;
        scanf("%d%d%d",&n,&m,&c);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&l[i]);
            have[l[i]]++;
        }
        for(int i=1;i<=n;i++)
        {
            add(n+l[i],i,0);
            if(have[l[i]+1]) add(i,n+l[i]+1,c);
            if(have[l[i]-1]) add(i,n+l[i]-1,c);
        }
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);add(v,u,w);
        }
        ll res=dij(1,n);
        printf("Case #%d: %lld\n",_,res>=1e12?-1:res);
    }

    return 0;
}
```
