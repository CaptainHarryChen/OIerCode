#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
 
bool zhishu(int a)
{
    int i;
    bool f=true;
	if(a==1)return 0;
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
    int n,m;
    cin>>n>>m;
    for(int i=n;i<=m;i++)
        if(zhishu(i)==true)
            cout<<i<<endl;
    return 0;
}

