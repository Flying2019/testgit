### [����](https://www.luogu.com.cn/problem/P3524)
���ݶ��壬$n$ ���ڵ�����в���������֮��û�б�������������˵�������֮��û�б���������ô������һ����ͬʱ���������ڡ�

��������ֻ��Ҫ�õ���СΪ $n$ ���ţ���ô���ǲ���ÿ���ҵ�һ��û�б����ڵĵ㣬Ȼ��ɾ���������㡣���Է���ɾ�� $n$ �Ե��ʣ�µ� $n$ ����һ�����š�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
#define M N*N/2
using namespace std;
struct node{
    int x,y;
}q[M];
bool mp[N][N],vis[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        mp[x][y]=mp[y][x]=true;
    }
    int tot=0;
    for(int i=1;i<=n && tot<n/3;i++)
    if(!vis[i])
        for(int j=i+1;j<=n;j++)
        if(!mp[i][j] && !vis[j])
        {
            vis[i]=vis[j]=true;
            tot++;
            break;
        }
    int p=n/3;
    for(int i=1;i<=n && p;i++)
    if(!vis[i])printf("%d ",i),--p;
    return 0;
}
```
