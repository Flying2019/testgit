#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 500010
using namespace std;
char s[N];
int nxt[N<<1],to[N<<1],head[N],cnt;
int tot[N][2];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
queue<int>q;
bool ban[N];
int main()
{
    int n,m;
    scanf("%d%d%s",&n,&m,s+1);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
        tot[u][s[v]-'A']++;tot[v][s[u]-'A']++;
    }
    for(int i=1;i<=n;i++)
    if(!tot[i][0] || !tot[i][1]) q.push(i),ban[i]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(ban[v]) continue;
            tot[v][s[u]-'A']--;
            if(!tot[v][0] || !tot[v][1]) q.push(v),ban[v]=true;
        }
    }
    for(int i=1;i<=n;i++)
    if(!ban[i]){puts("Yes");return 0;}
    puts("No");
    return 0;
}