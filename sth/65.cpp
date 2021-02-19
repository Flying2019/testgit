#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<ctime>
#include<algorithm>
#define N 1010
using namespace std;
int x[N],y[N],id[N],nid[N],w[N];
vector<int>g[N];
bool chs[N];
struct node{
    int u,v;
    bool operator <(const node a)const{return v<a.v;}
}p[N];
bool ansf[N];
int ansc,answ,n;
void work()
{
    int ans=0,c=0;
    for(int i=1;i<=n;i++)
    if(!chs[i])
    {
        bool ban=false;
        for(int v:g[i])
            if(chs[v]) ban=true;
        if(!ban) ans+=w[i],chs[i]=true,c++;
    }
    else ans+=w[i],c++;
    if(c>ansc || (c==ansc && answ>ans))
    {
        answ=ans,ansc=c;
        for(int i=1;i<=n;i++) ansf[i]=chs[i];
    }
}
int randint()
{
    static int f[N];int tt=0;
    for(int i=1;i<=n;i++)
    if(!chs[i]) f[tt++]=i;
    return f[rand()%tt];
}
void printint(int x){printf("%d%d%d",x/100,x/10%10,x%10);}
int main()
{
    srand(23333);
    int m;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++) scanf("%d%d",&p[i].u,&p[i].v);
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) id[p[i].u]=i,w[i]=p[i].v;
    for(int i=1;i<=m;i++) g[id[x[i]]].push_back(id[y[i]]),g[id[y[i]]].push_back(id[x[i]]);
    int tcnt=0;
    while(++tcnt<=500000)
    {
        work();
        if(ansc==n) break;
        int u=randint();
        for(int v:g[u]) chs[v]=false;chs[u]=true;
    }
    printf("%d\n",ansc);
    int p=0;
    for(int i=0;i<=1000;i++)
    if(ansf[id[i]])
    {
        if(p!=0) putchar(' ');
        else p=1;
        printint(i);
    }puts("");
    printf("%d",answ);
    return 0;
}