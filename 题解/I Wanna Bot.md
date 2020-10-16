### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102661/problem/F)
### ��Ŀ����
��һ��ͼ����һ����ɫȾɫ������Ҫ��ÿ��������������ڵ�һ����ͬɫ��

��֤ÿ�������������7��
### ���
���Ƕ�����������ʲô�ã������ԣ����ݸ���ԭ��������һ�������ڵĵ��У�~~������һ��bot���Ÿ���~~ ���ٴ���һ����ɫֻ��������һ�Ρ�Ҳ����˵���ٴ���һ�ֿ��з�����

�������ǿ���һ�ֲ��ԣ�����ÿ���㣬�����������Ҫ�󣬾��޸ĳ�ֻ��������һ�ε���ɫ��

���֤���������У�ע�⵽ÿ���޸Ķ��ǶԲ�����Ҫ��ĵ��޸ģ�Ҳ�������ٴ�������ͬɫ�ߡ����޸ĺ��������һ��ͬɫ�ߡ���ͬɫ�ߵ������� $O(m)$ �ģ�������ʱ�临�Ӷ�ȡ�����Ҳ�����Ҫ��ĵ㡣

����һ����**���**������Ҫ���Ҫǰ��������Χ�ĵ��޸ĳ�����ͬɫ�����Կ�����bfs��˼·��ÿ���޸ĵ�����Ƿ�������ڵ�ͬɫ�㣬������ھͼ�������޸��жϼ��ɡ�

���Ӷ� $O(m?)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#define N 100010
using namespace std;
vector<int>r[N];
int col[N];
queue<int>q;
bool in[N];
int n,m;
void work(int u)
{
    int swp[5]={0,0,0,0,0};
    for(int v:r[u])
    if(swp[col[v]])swp[col[v]]=-1;
    else swp[col[v]]=v;
    if(swp[col[u]]!=-1) return;
    for(int _=1;_<=4;_++)
    if(swp[_]>=0)
    {
        col[u]=_;
        if(swp[_] && !in[swp[_]])q.push(swp[_]),in[swp[_]]=true;
    }
}
void bfs()
{
    for(int i=1;i<=n;i++) q.push(i),in[i]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in[u]=false;
        work(u);
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    srand(n);
    for(int i=1;i<=n;i++) col[i]=rand()%4+1;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        r[u].push_back(v),r[v].push_back(u);
    }
    bfs();
    for(int i=1;i<=n;i++,puts(""))
        for(int _=1;_<=4;_++)
        if(col[i]!=_) printf("%d ",_);
    return 0;
}
```
