#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2010
using namespace std;
struct node{
    int x,y,z,id;
}p[N];
bool in(node a,node o,node b)
{
    if(min(a.x,b.x)>o.x || max(a.x,b.x)<o.x) return false;
    if(min(a.y,b.y)>o.y || max(a.y,b.y)<o.y) return false;
    if(min(a.z,b.z)>o.z || max(a.z,b.z)<o.z) return false;
    return true;
}
bool chs[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z),p[i].id=i;
    for(int i=1;i<=n;i++)
    if(!chs[i])
    {
        int k=0;
        for(int j=i+1;j<=n;j++)
        if(!chs[j] && (!k || in(p[i],p[j],p[k]))) k=j;
        chs[i]=chs[k]=true;
        printf("%d %d\n",i,k);
    }
    return 0;
}