#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define N 100010
using namespace std;
string a1("E.exe"),a2("E+.exe"),a3("randE.exe");
string t1("E.in"),t2("E.out"),t3("E+.out"),err("Err.txt");
string ex("rand.txt");
int main()
{
    int T=100;
    for(int i=1;i<=T;i++)
    {
        system((a3+"<"+ex+">"+t1).c_str());
        system((a1+"<"+t1+">"+t2).c_str());
        system((a2+"<"+t1+">"+t3).c_str());
        if(system((string("fc ")+t2+" "+t3+">"+err).c_str())){printf("WA on test %3d\n",i);return 1;}
        // _sleep(100);
        printf("Accepted on test %3d\n",i);
    }
    return 0;
}