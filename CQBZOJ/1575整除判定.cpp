#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    if(n%m==0)
        cout<<"YES"<<endl;
    else if(m%n==0)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}