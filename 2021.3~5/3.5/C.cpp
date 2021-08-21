#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 210
#define mod 1000000007
#define ll long long
using namespace std;
int tt;
struct matrix{
    int a[N][N];
    matrix(int c=0){memset(a,0,sizeof(a));for(int i=1;i<=tt;i++) a[i][i]=c;}
    int* operator [](int b){return a[b];}
}o,r;
matrix operator *(matrix a,matrix b)
{
    matrix swp;
    for(int i=1;i<=tt;i++)
        for(int k=1;k<=tt;k++)
            for(int j=1;j<=tt;j++)
            swp[i][j]=(swp[i][j]+1ll*a[i][k]*b[k][j])%mod;
    return swp;
}
void ksm(ll b)
{
    r=matrix(1);
    for(;b;b>>=1)
    {
        if(b&1) r=r*o;
        o=o*o;
    }
}
class ConversionMachine
{
    private:
    ll to[3][3];
    int id[13][13][13];//+0,+1,+2
    void add(int x,int y,int a)
    {
        if(!x || !y) return;
        o[x][y]+=a;
    }
    int dfs(int a,int b,int c)
    {
        if(a<0 || b<0 || c<0) return 0;
        if(!id[a][b][c]) id[a][b][c]=++tt;
        else return id[a][b][c];
        add(id[a][b][c],dfs(a-1,b,c+1),a);
        add(id[a][b][c],dfs(a+1,b-1,c),b);
        add(id[a][b][c],dfs(a,b+1,c-1),c);
        return id[a][b][c];
    }
    public:
    int countAll(string s,string t,vector<int>w,int m)
    {
        ll W=1ll*w[0]+w[1]+w[2];int n=s.size(),c=0;
        to[0][1]=w[0];to[1][2]=w[1];to[2][0]=w[2];
        to[0][2]=w[0]+w[1];to[1][0]=w[1]+w[2];to[2][1]=w[2]+w[0];
        int wc[3]={0,0,0};
        for(int i=0;i<n;i++)
        {
            int c1=s[i]-'a',c2=t[i]-'a';
            m-=to[c1][c2];
            if(m<0) return 0;
            wc[(c2-c1+3)%3]++;
        }
        c=wc[1]+wc[2]*2;
        m=m/W;
        int u=dfs(wc[0],wc[1],wc[2]),v=dfs(n,0,0);
        int ed=++tt;
        add(v,ed,1);add(ed,ed,1);
        ksm(3ll*m+c+1);
        return r[u][ed];
    }
};
// ConversionMachine F;
// int main()
// {
//     cout<<F.countAll(
// "aaaaaaaacaa",
// "aaaaaaaaaaa",
// {233,2333,23333},
// 1000000000
// );
//     return 0;
// }