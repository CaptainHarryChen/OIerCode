#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
 
bool zhishu(int a)
{
    int i;
    bool f=true;
    if(a==2)
        return f;
    for (i=2;i<sqrt(a)+1;i++)
    {
        if (a%i==0) 
        {
            f=false;
            break ;
        }
    }
    return f;
}
 
int main()
{
    int n,m,count=0;
    cin>>n>>m;
    for(int i=n;i<=m;i++)
        if(zhishu(i)==true)
            count++;
    cout<<count<<endl;
}