#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 50010
#define M 100010
using namespace std;
int a[N],n,m;
bitset<N>v[N],t;
int x[M],y[M];
bool vis[M],ans[M];
int c[]={0,1,1,1},g[]={0,1,2,3};
int main()
{
    int T;
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=m;i++) scanf("%d%d",&x[i],&y[i]);
    if(T==1)
    {
        t.set();
        for(int i=1;i<=n;i++) v[i].set(i);
        for(int i=m;i;i--) v[x[i]]=(v[y[i]]|=v[x[i]]);
        for(int i=1;i<=n;i++) t&=v[i];
        for(int i=1;i<=n;i++)
        if(t.test(i))
        {
            vis[i]=true;
            for(int p=m;p;p--)
            if(vis[y[p]]) ans[p]=true,vis[x[p]]=true;
            else vis[y[p]]=vis[x[p]];
            for(int i=1;i<=m;i++) putchar(ans[i]?'v':'^');
            return 0;
        }
        puts("-1");
    }
    else
    {
        if(n<=2){puts("-1");return 0;}
        for(int i=m;i;i--)
        if(y[i]<4)
        {
            ans[i]=c[g[x[i]]]>c[g[y[i]]];
            if(c[g[x[i]]]>c[g[y[i]]]) swap(x[i],y[i]);
            c[g[x[i]]]++,c[g[y[i]]]--;
            g[y[i]]=g[x[i]];
        }
        for(int i=1;i<=m;i++) putchar(ans[i]?'v':'^');
    }
    return 0;
}