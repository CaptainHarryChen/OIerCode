#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,j,k,i;
    cin>>n;
    int m[n];
    cin>>m[0];
    k=m[0];
    for(i=1;i<n;i++)
    {
        cin>>m[i];
        if(m[i]>k){k=m[i];j=i;}
    }
    m[j]=0;k=m[0];
    for(int i=0;i<n;i++)
        if(m[i]>k)k=m[i];
    cout<<k<<endl;
}