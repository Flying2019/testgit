#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define N 2010
using namespace std;
int n;
int mp[N][N];
int mx,my;
void upd(int x,int y)
{
    if(mp[x][y]<=mp[mx][my]) return;
    mx=x,my=y;
}
int qry(int x,int y,bool rev)
{
    if(x>n || x<1 || y>n || y<1) return 0;
    if(rev) swap(x,y);
    if(mp[x][y]) return mp[x][y];
    printf("? %d %d\n",x,y);
    fflush(stdout);
    int res;scanf("%d",&res);mp[x][y]=res;
    upd(x,y);
    return res;
}
void askmax(int x,int y,bool rev)
{
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++) qry(x+i,y+j,rev);
}
void answer(int x,int y,bool rev)
{
    if(rev) printf("! %d %d\n",y,x);
    else printf("! %d %d\n",x,y);
    exit(0);
}
void work(int lx,int rx,int ly,int ry,bool rev)
{
    if(rx-lx<ry-ly) swap(lx,ly),swap(rx,ry),rev^=1;
    int mid=(lx+rx)>>1,y=ly,vy=0;
    for(int i=ly;i<=ry;i++)
    {
        int v=qry(mid,i,rev);
        if(v>vy) vy=v,y=i;
    }
    int x=mid;
    askmax(x,y,rev);
    int px=rev?my:mx;
    if(px==mid) answer(mid,y,rev);
    if(px<mid) work(lx,mid-1,ly,ry,rev);
    else work(mid+1,rx,ly,ry,rev);
}
int main()
{
    scanf("%d",&n);
    work(1,n,1,n,0);
    return 0;
}