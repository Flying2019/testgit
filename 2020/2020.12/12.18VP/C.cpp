#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
const char s[4][8][8]={
    {
        "abcc",
        "abdd",
        "ccab",
        "ddab"},
    {
        "abbcc",
        "ad..e",
        "ed..e",
        "e.aac",
        "aabbc"},
    {
        "aabbcc",
        ".d.d.d",
        ".d.d.d",
        "d.d.d.",
        "d.d.d.",
        "aabbcc"},
    {
        ".aabbcc",
        "abcc...",
        "ab.a...",
        "bcca...",
        "b...abb",
        "a...a.a",
        "a...bba"}
};
int p=1,n;
char res[1010][1010];
void print(int x)
{
    n-=x+4;
    for(int i=0;i<x+4;i++)
        for(int j=0;j<x+4;j++) res[p+i][p+j]=s[x][i][j];
    p+=x+4;
}
int main()
{
    scanf("%d",&n);
    int m=n;
    if(n<=3)
    {
        if(n<=2) puts("-1");
        else puts("a..\na..\n.bb");
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) res[i][j]='.';
    print(n%4);
    while(n) print(0);
    for(int i=1;i<=m;i++) printf("%s\n",res[i]+1);
    return 0;
}