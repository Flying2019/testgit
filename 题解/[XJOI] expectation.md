### [����](http://115.236.49.52:83/contest/1537/problem/1)
���ȿ�����μ�����С��������������

��Ȼ��ͬ��С��������ĳһ���ȵıߵ�����������ͬ�ġ��������ǲ����Ƚ�����С��������

���������Ƕ���ĳһ���ȵıߣ����Ǽ�������������С�������г��˸ó��ȵ������ߣ���ô�ó��ȵĿ��з���������������������������

��ô�������Ϳ���ͨ������������㶨��

���������ǿ���������ֵ����Ȼ���Ƕ���ĳһ���ȵı߼��������з����ļ�ֵ�ͳ��Է���������ô�𰸾������г��ȵıߵ������͡�

�������ͳ�ơ����Է��־������б�������

$$\sum_{P\in M}{[P \text{��ĳһ���߼���}]}\ {\prod_{s\in P}W_s}$$

���ʽ��û�����ֵ�͡����ǲ����� $W_s=1+w_sx$��

$$\sum_{P\in M}{[P \text{��ĳһ���߼���}]}\ {\prod_{s\in P}(1+w_sx)}$$

����ȡ������ $[x^1]$ ��ϵ�������Է���
$$\sum_{P\in M}{[P \text{��ĳһ���߼���}]}\ 1+x{\sum_{s\in P}w_s}$$
���Է��ֳ�������Ƿ�������$x$ һ����ϵ���������з����ļ�ֵ�͡�

�������ǲ�������һ����Ԫ�� $(a,b)$ ��ʾ $a+bx(\bmod x^2)$�����¶������������㡣���� $+-$ ����Ȼ��$(a,b)\times(c,d)=(ac,ad+bc)$��$\frac{(a,b)}{(c,d)}=\left(\frac a c,\frac{ad-bc}{c^2}\right)$��

������ʽ�Ӵ����˹��Ԫ���ɡ����Ӷ� $O(m\times d^3)$��
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 200010
#define ll long long
using namespace std;
struct matrix_tree{
    #define M 66
    #define eps 1e-6
    struct node{
        long double c,k;//kx+c
        node(long double C=0,long double K=0):c(C),k(K){}
        node operator +(node a){return node(c+a.c,k+a.k);}
        void operator +=(node a){c+=a.c,k+=a.k;}
        node operator -(node a){return node(c-a.c,k-a.k);}
        void operator -=(node a){c-=a.c,k-=a.k;}
        node operator *(node a){return node(c*a.c,k*a.c+c*a.k);}
        node operator /(node a){return node(c/a.c,(k*a.c-c*a.k)/a.c/a.c);}
    };
    node num[M][M];
    void clear(){for(int i=0;i<M;i++) for(int j=0;j<M;j++) num[i][j]=node(0,0);}
    void add(int u,int v,int w)
    {
        num[u][u]-=node(1,w);
        num[v][v]-=node(1,w);
        num[u][v]+=node(1,w);
        num[v][u]+=node(1,w);
    }
    double gauss(int n)
    {
        for(int i=1;i<n;i++)
        {
            int u=i;
            for(int j=i+1;j<n;j++)
            if(fabs(num[j][i].c)>fabs(num[u][i].c)) u=j;
            if(u!=i)
                for(int j=1;j<n;j++) swap(num[i][j],num[u][j]);
            for(int k=i+1;k<n;k++)
            {
                node del=num[k][i]/num[i][i];
                for(int j=i;j<n;j++)
                    num[k][j]=num[k][j]-num[i][j]*del;
            }
        }
        long double ans=0;
        for(int i=1;i<n;i++) ans+=num[i][i].k/num[i][i].c;
        return ans;
    }
}g;

struct road{
    int x,y,v,w;
    bool operator <(const road a)const{return v<a.v;}
}r[N],rd[N];
int ccnt,id[N],f[N],tcnt,cnt;
bool chs[N];
vector<road>v[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++) scanf("%d%d%d%d",&r[i].x,&r[i].y,&r[i].v,&r[i].w);
    sort(r+1,r+m+1);
    for(int i=1;i<=m;i++)
    {
        if(!i || r[i].v!=r[i-1].v) ++ccnt;
        v[ccnt].push_back(r[i]);
        int hx=find(r[i].x),hy=find(r[i].y);
        if(hx==hy) continue;
        f[hx]=hy;
        chs[ccnt]=true;
        rd[++cnt]=r[i];
        rd[cnt].v=ccnt;
    }
    if(cnt!=n-1){puts("0.00000");return 0;}
    long double ans=0;
    for(int i=1;i<=ccnt;i++)
    if(chs[i])
    {
        if(v[i].size()==1){ans+=v[i][0].w;continue;}
        for(int j=1;j<=n;j++) f[j]=j;
        for(int j=1;j<=cnt;j++)
        if(rd[j].v!=i) f[find(rd[j].x)]=find(rd[j].y);
        int t=0;
        for(int j=1;j<=n;j++)
        if(f[j]==j) id[j]=++t;
        for(int j=1;j<=n;j++) id[j]=id[find(j)];
        g.clear();
        for(road u:v[i])
        g.add(id[u.x],id[u.y],u.w);
		ans+=g.gauss(t);
    }
    printf("%.5Lf\n",ans);
    return 0;
}
```
