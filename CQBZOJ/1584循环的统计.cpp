#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,m=0;
    cin>>n;
    for(int i=0,j=1;i<n;i++,j+=i+1)
        m+=j;
    cout<<m<<endl;
}
