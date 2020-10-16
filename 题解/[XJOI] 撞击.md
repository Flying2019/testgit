### [����](http://115.236.49.52:83/contest/1534/problem/2)
���ɼ��㼸���⡣����

���ȣ�ʯͷ�˶��ɻ�Ҳ���˶����ѿ��ǣ����Բ�����ĳ��ʯͷΪ�ο�ϵ����ô�ɴ����ٶȷ��������ʯͷ�ķ�������

������˵������ɴ��ķ��з���Ϊ $x\in[0,2\pi)$����Ȼ�ɴ����ٶ����� $\vec{v}=(v\cos x,v\sin x)$����ʯͷ���ٶ����� $\vec{v_i}=(x_i,y_i)$����ô�� $i$ ʯͷΪ�ο�ϵ���ɴ����ٶ����� $\vec{v}=(v\cos x-x_i,v\sin x-y_i)$��

���Է��֣���������·ɴ����ٶ������ļ�����һ���� $(-x_i,-y_i)$ ΪԲ�ģ�$v$ Ϊ�뾶��Բ��

���Է���ĳ������ $x$ ����ײ��ʯͷ $i$�����ҽ��� $(0,0)$ �� $x$ �����������Բ $i$ �н����������������Է��֣�����һ��������������ɵ���������ʹ�ö��������������е����߶��н���

���Է��֣��ٶ�������Բ��λ�������еĲ��־��Ǹ�ʯͷ�Ĺ��ס�����������ۼ��ɡ�

��ôʣ�µĲ��־��ǣ���һЩԲ�ϵ����䣬����ÿ�ָ��Ǵ��� $x$���󱻸����� $x$ �ε�Բ�����ȡ�

��Ȼ��������串�ǣ��������򼴿ɡ��ر�ģ�Բ�Ͽ��ܻ���� $l>r$ �����䣬������������һȦ������ $[2,2\pi+1]$ ������Բ���� $[2,1]$ ���䣩��Ϊ�˷������ǻ��ǿ��� $p_l+1,p_r-1$�����Է��������õ��������ȥ�� $[r,l]$ �Ĺ��ף�����ֱ�ӽ������+1���ɡ�

���Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#define N 100010
#define db double
#define P pair<db,db>
#define Pi pair<db,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
const db pi=acos(-1),eps=1e-9;
db rand(db x){return x+(rand()%10)*1.0/10.0*eps;}
struct point{
    db x,y;
    point(db X=0.0,db Y=0.0):x(X),y(Y){}
    point operator +(point a){return point(x+a.x,y+a.y);}
    point operator -(point a){return point(x-a.x,y-a.y);}
    db operator *(point a){return x*a.y-y*a.x;}
    point operator /(db a){return point(x/a,y/a);}
    point operator *(db a){return point(x*a,y*a);}
    db slp(){return atan2(y+eps,x+eps);}
}v[N];
vector<Pi >res;
db dis(point a){return sqrt(a.x*a.x+a.y*a.y);}
struct cir{
    point o;
    db r;
    cir(db X=0.0,db Y=0.0,db R=0.0):o(X,Y),r(R){}
}c[N];
point to_cir(db x){return point(cos(x),sin(x));}
inline db modp(db x){return x<0?x+2*pi:(x>2*pi?x-2*pi:x);}
P qie(cir c)
{
    db a=modp(c.o.slp()),b=asin(c.r/dis(c.o));
    return MP(modp(a-b),modp(a+b));
}
vector<db> t;
void work(cir p,db a)
{
    if(p.o.x==0 && p.o.y==0){t.push_back(a),t.push_back(modp(a+pi));return;}
    db o=modp(a-pi/2),d=dis(p.o)*sin(p.o.slp()-a);
    if(abs(d-dis(p.o))<=eps){t.push_back(o);return;}
    db dta=acos(d/p.r);
    t.push_back(modp(o-dta)),t.push_back(modp(o+dta));
}
db solve(db l,db r,cir p,P v){db x=l<r?(l+r)/2:modp((l+r)/2-pi);return modp((p.o+to_cir(x)*p.r).slp());}
db v0,ans[N];
inline bool line_in(db l,db r,db x){return l>r?(x>=l-eps || x-eps<=r):(x>=l-eps && x-eps<=r);}
int main()
{
    int n;
    scanf("%d%lf",&n,&v0);
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf%lf%lf",&c[i].o.x,&c[i].o.y,&c[i].r,&v[i].x,&v[i].y);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        cir f(-v[i].x,-v[i].y,v0);
        if(dis(c[i].o)<=c[i].r+eps){++cnt; continue;}
        if(!c[i].r) continue;
        t.clear();
        P u=qie(c[i]);
        if(dis(v[i])>=v0-eps)
        {
            P s=qie(f);
            if(line_in(s.fi,s.se,u.fi)) work(f,u.fi);
            if(line_in(s.fi,s.se,u.se)) work(f,u.se);
        }
        else work(f,u.fi),work(f,u.se);
        if(t.empty()){cnt+=line_in(solve(0,1,f,u),u.fi,u.se);continue;}
        sort(t.begin(),t.end());
        t.push_back(t[0]);
        for(int j=0;j<t.size()-1;j++)
        if(line_in(solve(t[j],t[j+1],f,u),u.fi,u.se))
        {
            res.push_back(MP(t[j],1)),res.push_back(MP(t[j+1],-1));
            if(t[j]>t[j+1]) ++cnt;
        }
    }
    res.push_back(MP(2*pi,0));
    sort(res.begin(),res.end());
    db p=0;
    for(Pi u:res)
    {
        ans[cnt]+=u.fi-p;
        cnt+=u.se,p=u.fi;
        // printf("%d: %.3lf - %.3lf\n",cnt,p,u.fi);
    }
    for(int i=0;i<=n;i++) printf("%.3lf ",ans[i]*1.0/pi/2);
    return 0;
}
```
