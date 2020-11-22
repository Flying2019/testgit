#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
char s[N];
bool chs[N];
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    int l=1,r=n;
    for(;l<=r;l++,r--)
    {
        if(s[l]==s[r]) chs[l]=chs[r]=true;
        else
        {
            if(l+2>=r) {chs[l]=true;break;}
            if(s[l]==s[r-1]){chs[l]=chs[r-1]=true;r--;}
            else if(s[l+1]==s[r]){chs[l+1]=chs[r]=true;l++;}
            else if(s[l+1]==s[r-1]){chs[l+1]=chs[r-1]=true;l++;r--;}
        }
    }
    for(int i=1;i<=n;i++)
    if(chs[i]) putchar(s[i]);
    return 0;
}