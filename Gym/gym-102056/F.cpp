#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
using namespace std;
typedef double db;
const db pi=acos(-1),eps=1e-9;
struct node{
    db x,y,z;
    node(db X=0,db Y=0,db Z=0):x(X),y(Y),z(Z){}
    node operator +(const node a)const{return node(x+a.x,y+a.y,z+a.z);}
    node operator -(const node a)const{return node(x-a.x,y-a.y,z-a.z);}
};
node operator *(const node a,const node b)
{
    return node(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
db dis2(node a){return a.x*a.x+a.y*a.y+a.z*a.z;}
db dis(node a){return sqrt(dis2(a));}
db angle(node A,node B,node C)//< AB , BC >
{
    db b=dis(A-C),c=dis(A-B),a=dis(B-C);
    if(a<eps || c<eps) return pi/2;
    return acos((a*a+c*c-b*b)/(2*a*c));
}
db dist(node A,node B,node C)//The distance from B to AC
{
    return dis((A-B)*(C-B))/dis(A-C);
}
node o,s,t;db r;
int main()
{
    int T;
    scanf("%d",&T);
    while(T --> 0)
    {
        scanf("%lf%lf%lf%lf",&o.x,&o.y,&o.z,&r);
        scanf("%lf%lf%lf%lf%lf%lf",&s.x,&s.y,&s.z,&t.x,&t.y,&t.z);
        if(dis(s-t)<eps || dist(s,o,t)>=r || angle(s,t,o)>=pi/2 || angle(t,s,o)>=pi/2){printf("%.7lf\n",dis(s-t));continue;}
        db alp=angle(s,o,t);
        db bs=acos(r/dis(o-s)),bt=acos(r/dis(o-t));
        printf("%.7lf\n",r*(alp-bs-bt)+sqrt(dis2(s-o)-r*r)+sqrt(dis2(t-o)-r*r));
    }
    return 0;
}