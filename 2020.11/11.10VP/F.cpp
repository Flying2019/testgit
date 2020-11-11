#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define N 50010
#define db double
#define eps 1e-8
using namespace std;
short int cmp(db a,db b=0){if(fabs(a-b)<=eps) return 0;return a<b?-1:1;}
struct point{
    db x,y;
    int id;
    point(db X=0,db Y=0,int I=0):x(X),y(Y),id(I){}
    point operator +(point a){return point(x+a.x,y+a.y);}
    point operator -(point a){return point(x-a.x,y-a.y);}
    point operator *(db a){return point(x*a,y*a);}
    point operator /(db a){return point(x/a,y/a);}
    friend bool operator <(point a,point b)
    {
        if(cmp(a.x,b.x)==0) return a.y<b.y;
        else return a.x<b.x;
    }
}p[N],sp[N];
db dis(point a){return sqrt(a.x*a.x+a.y*a.y);}
struct H{
    db x;int id;
    H(db X=0,int I=0):x(X),id(I){}
    bool operator <(const H a)const{return x<a.x;}
}q[N];
int qt,n;
double X;
struct Line{
    double k,b,l,r;
    int id;
    friend bool operator <(const Line a,const Line b)
    {
        double va=a.k*X+a.b,vb=b.k*X+b.b;
        if(cmp(va,vb)==0) return a.id<b.id;
        return va<vb;
    }
    Line(){k=b=l=r=0;id=0;}
    Line(point a1,point a2,int I=0)
    {
        if(a1.x>a2.x) swap(a1,a2);
        l=a1.x,r=a2.x;
        k=(a2.y-a1.y)/(a2.x-a1.x);b=a1.y-k*a1.x;
        id=I;
    }
}li[N];
bool jiao(Line a,Line b)
{
    double vk=a.k-b.k,vb=b.b-a.b;
    if(cmp(vk)==0) return !cmp(a.b,b.b) && cmp(a.r,b.l)>=0 && cmp(a.l,b.r)<=0;
    double x=vb/vk;
    return cmp(a.l,x)<=0 && cmp(x,a.r)<=0 && cmp(b.l,x)<=0 && cmp(x,b.r)<=0;
}
multiset<Line>mt;
multiset<Line>::iterator in[N];
bool check(db T)
{
    qt=0;
    for(int i=1;i<=n;i++)
    {
        li[i]=Line(p[i],p[i]+sp[i]*T,i);
        q[++qt]=H(li[i].l,i);
        q[++qt]=H(li[i].r-eps,-i);
    }
    sort(q+1,q+qt+1);
    mt.clear();
    for(int i=1;i<=qt;i++)
    {
        int u=q[i].id>0?q[i].id:-q[i].id;X=q[i].x;
        if(q[i].id>0)
        {
            auto it=mt.insert(li[u]),iv=it;in[u]=it;
            if(it!=mt.begin()){--iv;if(jiao(*it,*iv)) return true;}
            iv=it;iv++;
            if(iv!=mt.end()){if(jiao(*it,*iv)) return true;}
        }
        else
        {
            auto it=in[u],il=it,ir=it;++ir;
            if(ir!=mt.end() && il!=mt.begin())
            {
                il--;
                if(jiao(*il,*ir)) return true;
            }
            mt.erase(it);
        }
    }
    return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        db s;
        scanf("%lf%lf%lf%lf%lf",&p[i].x,&p[i].y,&sp[i].x,&sp[i].y,&s);
        // printf("%.6f %.6f %.6f %.6f %.6f\n",sp[i].x,sp[i].y,dis(sp[i]),(sp[i]/dis(sp[i])).x,(sp[i]/dis(sp[i])).y);
        sp[i]=sp[i]/dis(sp[i])*s;
    }
    db l=0,r=2e12;
    while(r-l>max(r*1e-7,1e-7))
    {
        db T=(l+r)/2;
        if(check(T)) r=T;
        else l=T;
    }
    if(l>=1e12) puts("No show :(");
    else printf("%.7f",l);
    return 0;
}