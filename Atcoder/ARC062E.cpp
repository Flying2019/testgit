#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#define ll long long
#define N 410
using namespace std;
struct node{
    int p[4];
    node(int a=0,int b=0,int c=0,int d=0){p[0]=a;p[1]=b;p[2]=c;p[3]=d;}
    void rot(){for(int i=0;i<3;i++) swap(p[i],p[i+1]);}
}a[N];
bool operator <(const node a,const node b)
{
    for(int t=0;t<4;t++)
        if(a.p[t]!=b.p[t]) return a.p[t]<b.p[t];
    return false;
}
node operator <<(node a,int p){for(int i=0;i<p%4;i++) a.rot();return a;}
node operator |(node a,node b){return node(a.p[1],a.p[0],b.p[0],b.p[3]);}
vector<node> all_node(node a){return {a,a<<1,a<<2,a<<3};}
map<node,int>mp;
void ins(node u,int v){for(auto p:all_node(u)) mp[p]+=v;}
node sw[5];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",&a[i].p[0],&a[i].p[1],&a[i].p[2],&a[i].p[3]);
    for(int i=1;i<=n;i++) ins(a[i],1);
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        ins(a[i],-1);node u=a[i];
        for(int j=i+1;j<=n;j++)
        {
            ins(a[j],-1);
            for(auto v:all_node(a[j]))
            {
                for(int k=0;k<4;k++,u=u<<1,v=v<<3) sw[k]=u|v;
                bool can=true;
                for(int k=0;k<4 && can;k++)
                if(!mp.count(sw[k])) can=false;
                if(!can) continue;
                ll res=1;
                for(int k=0;k<4;k++) res*=mp[sw[k]],ins(sw[k],-1);
                for(int k=0;k<4;k++) ins(sw[k],1);
                ans+=res;
            }
            ins(a[j],1);
        }
    }
    printf("%lld",ans);
    return 0;
}