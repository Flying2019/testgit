#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 200010
#define M 200000000
#define db double
using namespace std;
const db pi=acos(-1),dt=10*(2-pi/2);
struct node{
    int x,y;
    bool operator <(const node a)const{return x<a.x;}
}p[N];
int q[N],qt;
int main()
{
    int x1,y1,x2,y2,n;
    scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&n);
    bool tx=0,ty=0;
    if(x1>x2) x1=M-x1,x2=M-x2,tx=true;
    if(y1>y2) y1=M-y1,y2=M-y2,ty=true;
    int tt=0;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(tx) x=M-x;if(ty) y=M-y;
        if(x1<=x && x<=x2 && y1<=y && y<=y2) p[++tt]=(node){x,y};
    }
    sort(p+1,p+tt+1);
    db d=(x2-x1+y2-y1)*100.0;
    memset(q,0x3f,sizeof(q));
    for(int i=1;i<=tt;i++)
    {
        int l=lower_bound(q+1,q+tt+1,p[i].y)-q;
        q[l]=p[i].y;
    }
    int res=0;
    for(int i=1;i<=tt;i++)
    if(q[i]<=M) res++;
    if(res==x2-x1+1 || res==y2-y1+1) d+=5*pi;
    printf("%.11lf",d-dt*res);
    return 0;
}