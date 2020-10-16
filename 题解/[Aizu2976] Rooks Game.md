### [����](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2976)
### ��Ŀ����
����������һЩ�����������һ����������ͬһ�Ż�ͬһ������һ�����������Ϳ����ƶ���ȥ���Ե��Ǹ������������û�С������ᱻ�Ե�����ֹ������

����󱻳Ե��ġ����������������ֵ����Сֵ��
### ���
��ȻҪ�������ۡ����Է��֡��ԡ��ı��ʿ��Կ��ɽ�ֱ�ӽ���ǰ�ġ������Ƴ���

���������Ի���Ե��ġ�����֮����һ���ߣ����������ֵ����������ȥ��ͨ����������Ϊһ����ͨ������Ҫʣһ����

�ٿ������ֵ������Ȼ��һ��ƽ���������Ӽ����⣬ֱ�����н�����һ�߶���ͼƥ�伴�ɡ�

���Ӷ� $O(n^2)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 2010
using namespace std;
int f[N],link[N],n;
bool vis[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
struct node{
    int x,y;
}p[N];
vector<int>g[N];
bool check(int x)
{
    vis[x]=true;
    for(int v:g[x])
    {
        if(!link[v] || (!vis[link[v]] && check(link[v])))
        {
            link[v]=x;
            return true;
        }
    }
    return false;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    int k=m;
    for(int i=1;i<=m;i++) scanf("%d%d",&p[i].x,&p[i].y),f[i]=i;
    for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++)
        if(p[i].x==p[j].x || p[i].y==p[j].y)
        {
            int hx=find(i),hy=find(j);
            if(hx!=hy) f[hx]=hy,--k;
        }
    for(int i=1;i<=m;i++)
    g[p[i].x].push_back(p[i].y);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if(check(i)) ++ans;
    }
    printf("%d %d\n",m-ans,m-k);
    return 0;
}
```
