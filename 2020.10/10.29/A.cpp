#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<map>
#define mod 998244353
#define N 200010
using namespace std;
string s;
#define M 12
struct matrix{
    int a[M+2][M+2];
    int* operator [](int b){return a[b];}
    matrix(){memset(a,0,sizeof(a));}
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        for(int i=0;i<M;i++)
            for(int k=0;k<M;k++)
                for(int j=0;j<M;j++) c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
        return c;
    }
}a,r;
matrix ksm(matrix a,int k)
{
    matrix o;for(int i=0;i<M;i++) o[i][i]=1;
    for(;k;k>>=1)
    {
        if(k&1) o=o*a;
        a=a*a;
    }
    return o;
}
string B[]={"","a","b","ab","ba","bb","aba","bab","abb","bba","babb","bbab"};
string U[]={"aa","abab","abba","baba","babba","bbaba","bbabb","bbb"};
string V[]={"","bba","bab","abb","bbab","babb","aba",""};
map<string,int>id;
map<string,string>nxt;
int base(string s)
{
    string u="";
    for(int i=0;i<s.size();i++)
    {
        u+=s[i];
        for(int j=u.size()-1;j>=max((int)u.size()-5,0);j--)
        if(nxt.count(u.substr(j,u.size())))
        {
            string v=nxt[u.substr(j,u.size())];
            u.erase(j);u+=v;break;
        }
    }
    // cout<<u<<endl;cout<<id[u]<<endl;
    return id[u];
}
int main()
{
    for(int i=0;i<12;i++) id[B[i]]=i;
    for(int i=0;i<8;i++) nxt[U[i]]=V[i];
    cin>>s;
    base(s);
    int n;
    scanf("%d",&n);
    int u=base(s);
    for(int i=0;i<12;i++) a[i][base(B[i]+"a")]=a[i][base(B[i]+"b")]=1;
    r=ksm(a,n);
    printf("%d\n",r[0][u]);
    return 0;
}