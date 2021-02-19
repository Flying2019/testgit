#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 10010
#define M 100010
using namespace std;
vector<int>gu[N],gv[N],c[N];
bool cir[N];
struct node{
    int u,w,c;
    bool operator <(const node a)const{return w!=a.w?w>a.w:c>a.c;}
};
int preu[N],prec[N];
int disw[N],disc[N];
bool vis[N];
priority_queue<node>q;
#define abs(x) ((x)>0?(x):-(x))
void dij(int s,int t)
{
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));memset(disw,0x3f,sizeof(disw));memset(disc,0x3f,sizeof(disc));
    disw[s]=disc[s]=0;q.push((node){s,0,0});
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        if(vis[u]) continue;
        if(u==t) return;
        vis[u]=true;
        int sz=gu[u].size();
        for(int i=0;i<sz;i++)
        {
            auto &p=c[gu[u][i]];
            int s=p.size(),pu=gv[u][i];
            for(int j=0;j<s;j++)
            {
                int w=!cir[gu[u][i]]?abs(j-pu):min(abs(j-pu),s-abs(j-pu));
                if(disw[p[j]]>disw[u]+w || (disw[p[j]]==disw[u]+w && disc[p[j]]>disc[u]+1))
                {
                    disw[p[j]]=disw[u]+w,disc[p[j]]=disc[u]+1;
                    preu[p[j]]=u,prec[p[j]]=gu[u][i];
                    q.push((node){p[j],disw[p[j]],disc[p[j]]});
                }
            }
        }
    }
}
void printnum(int a){printf("%d%d%d%d",a/1000,(a/100)%10,(a/10)%10,a%10);}
void print(int s,int t)
{
    if(s==t) return;
    print(s,preu[t]);
    printf("Take Line#%d from ",prec[t]);
    printnum(preu[t]);
    printf(" to ",prec[t]);
    printnum(t);
    puts(".");
}
int main()
{
    int p;
    scanf("%d",&p);
    for(int i=1;i<=p;i++)
    {
        int s;
        scanf("%d",&s);
        if(s==1) continue;
        for(int j=0;j<s;j++)
        {
            int u;
            scanf("%d",&u);
            if(j==s-1 && u==c[i][0]){cir[i]=true;break;}
            c[i].push_back(u);gu[u].push_back(i);gv[u].push_back(j);
        }
    }
    int m;
    scanf("%d",&m);
    while(m --> 0)
    {
        int s,t;
        scanf("%d%d",&s,&t);
        dij(s,t);
        printf("%d\n",disw[t]);
        print(s,t);
    }
    return 0;
}