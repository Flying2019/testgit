#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define N 100010
using namespace std;
string a1("J.exe"),a2("J-.exe"),a3("randJ.exe");
string t1("J.in"),t2("J.out"),t3("J-.out"),err("Err.txt");
string ex("randJ.txt");
int main()
{
    int T=10000;
    for(int i=1;i<=T;i++)
    {
        system((a3+"<"+ex+">"+t1).c_str());
        system((a1+"<"+t1+">"+t2).c_str());
        system((a2+"<"+t1+">"+t3).c_str());
        //system(a3.c_str());
        //system(a1.c_str());
        //system(a2.c_str());
        if(system((string("fc ")+t2+" "+t3+">"+err).c_str())){printf("WA on test %3d\n",i);return 1;}
        // _sleep(100);
        printf("Accepted on test %3d\n",i);
    }
    return 0;
}