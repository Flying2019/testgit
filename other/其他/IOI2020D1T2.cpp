#include<vector>
#include<queue>
#include<algorithm>
#define ll long long
#define N 2010
using namespace std;
extern "C"
void allocate_tickets(vector<vector<int> >r);
struct node{
    int u,v;
    node(int U=0,int V=0):u(U),v(V){}
    bool operator <(const node a)const{return v<a.v;}
};
priority_queue<node>q;
int tt[N],lf[N],rf[N],id[N];
bool cmp(int x,int y){return tt[x]<tt[y];}
// void allocate_tickets(vector<vector<int> >&r)
// {
//     for(int i=0;i<r.size();i++,puts(""))
//         for(int j=0;j<r[i].size();j++) printf("%d ",r[i][j]);
// }
extern "C"
ll find_maximum(int k,vector<vector<int> >x)
{
    int n=x.size(),m=x[0].size();ll ans=0;
    vector<vector<int> >res;
    res.resize(n);
    for(int i=0;i<n;i++)
    {
        id[i]=i,rf[i]=m-1;
        for(int j=0;j<m;j++) res[i].push_back(-1);
        for(int j=0;j<k;++j) ans-=x[i][j];
        q.push(node(i,x[i][m-1]+x[i][k-1])),tt[i]=1;
    }
    for(int p=0;p<n*k/2;p++)
    {
        int i=q.top().u;q.pop();
        ans+=x[i][m-tt[i]]+x[i][k-tt[i]];++tt[i];
        if(tt[i]<=k) q.push(node(i,x[i][m-tt[i]]+x[i][k-tt[i]]));
    }
    for(int p=0;p<k;p++)
    {
        sort(id,id+n,cmp);
        for(int i=0;i<n/2;i++) res[id[i]][lf[id[i]]++]=p;
        for(int i=n/2;i<n;i++) res[id[i]][rf[id[i]]--]=p,--tt[id[i]];
    }
    allocate_tickets(res);
    return ans;
}
// int main()
// {
//     int n,m,k;vector<vector<int> >x;
//     scanf("%d%d%d",&n,&m,&k);x.resize(n);
//     for(int i=0;i<n;i++) x[i].resize(m);
//     for(int i=0;i<n;i++)
//         for(int j=0;j<m;j++) scanf("%d",&x[i][j]);
//     printf("%lld\n",find_maximum(k,x));
// }