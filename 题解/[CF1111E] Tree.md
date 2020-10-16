### [����](https://codeforces.com/problemset/problem/1120/E)
������δ�����ѯ�ʡ������������ǰ��� $r$ Ϊ����dfs�������������dfs��������Ȼ������ $i$ ��������ȶ��� $i$ ǰ�档������Ϊ $g_i$��������������������

��Ȼ���ȵ����Ȼ������ȣ������� $g_i$ ��������ڲ�ͬ�����С�

�� $f_{i,j}$ ��ʾǰ $i$ ����ֳ� $j$ ��ķ�������ô��Ȼ���Խ���ǰ $i$ �ֵ������� $j-g_i$ ���У����߶࿪һ�飬�� $f_{i,j}=f_{i-1,j-1}+\max(j-g_i,0)\times f_{i-1,j}$��

���Է��� $m$ ��С�����Ը��Ӷȿ��Խ��ܡ�

���Ǵ�����ѯ�ʡ���Ϊֱ�ӻ����� $O(n)$ ����Ȼ���ܽ��ܣ�~~����LCT����~~��������Ҫ�󵽸�·���ϵĵ�ĸ�������ȫ��������״���鵥���޸�����ѯ����Ȼ�߶���Ҳ���ԡ�

��ʱ�临�Ӷ� $O(\sum k\log n+m\sum k)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define mod 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void addr(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int dep[N],fa[N],son[N],siz[N];
int id[N],top[N],nid[N],tot;
void dfs(int u,int p)
{
    fa[u]=p;
    siz[u]=1;
    dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int topp)
{
    top[u]=topp;
    id[u]=++tot,nid[tot]=u;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa[u] || v==son[u]) continue;
        dfs2(v,v);
    }
}
int val[N],n;
inline int lowbit(int x){return x&(-x);}
int add(int x,int v){for(;x<=n;x+=lowbit(x)) val[x]+=v;}
int answer(int x){int ans=0;for(;x;x-=lowbit(x)) ans+=val[x];return ans;}
int qry(int l,int r){return answer(r)-answer(l-1);}
int line_q(int x,int y)
{
    int ans=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans+=qry(id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return ans+qry(id[x],id[y]);
}
int a[N],rs[N],f[N][305];
bool cmp(int x,int y){return f[x]<f[y];}
int main()
{
    int q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addr(u,v),addr(v,u);
    }
    dfs(1,0),dfs2(1,1);
    while(q --> 0)
    {
        int k,m,r;
        scanf("%d%d%d",&k,&m,&r);
        for(int i=1;i<=k;i++) scanf("%d",&a[i]),add(id[a[i]],1);
        for(int i=1;i<=k;i++) rs[a[i]]=line_q(a[i],r)-1,printf("%d:%d\n",a[i],rs[a[i]]);
        sort(a+1,a+k+1,cmp);
        f[1][1]=1;
        for(int i=2;i<=k;i++)
            for(int j=1;j<=min(i,m);j++)
            {
                f[i][j]=f[i-1][j-1];
                if(j-rs[a[i]]&gt;=0) f[i][j]=(f[i][j]+1ll*f[i-1][j]*(j-rs[a[i]])%mod)%mod;
            }
        int ans=0;
        for(int i=1;i<=m;i++) ans=(ans+f[k][i])%mod;
        printf("%d\n",ans);
        for(int i=1;i<=k;i++) add(id[a[i]],-1),rs[a[i]]=0;
        for(int i=1;i<=k;i++)
            for(int j=1;j<=min(i,m);j++) f[i][j]=0;
    }
    return 0;
}
```
