#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char s[N];
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    int c=0;bool d=0;
    for(int i=1;i<=n;i++)
    {
        ++c;
        if(d || s[i]!=s[i-1]) d=false;
        else if(i==n) c--;
        else i++,d=true;
    }
    printf("%d\n",c);
    return 0;
}