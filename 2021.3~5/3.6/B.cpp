#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100010
#define inf 100000000
using namespace std;
struct node{
    int s,t;
    bool operator <(const node a)const{return t<a.t;}
}p[N];
int operator +=(int &a,node b){a+=b.s;return max(a-b.t,0);}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d",&p[i].s,&p[i].t);
        sort(p+1,p+n+1);
        int r=0,m1=0,m2=0,c=0,d=0;
        auto chk=[&](int d){if(d>m1) m2=m1,m1=d;else if(d>m2) m2=d;};
        for(int i=1;i<=n;i++)
        {
            d=c+=p[i];
            if(d>m2) r=i;
            chk(d);
        }
        int ans=m1+m2;
        for(int i=1;i<=r;i++)
        {
            node u=p[i];p[i]=(node){0,inf};
            m1=m2=c=0;
            for(int j=1;j<=r;j++) chk(d=c+=p[j]);
            chk(d=c+=u);
            p[i]=u;
            ans=min(ans,m1+m2);
        }
        printf("%d\n",ans);
    }
    return 0;
}