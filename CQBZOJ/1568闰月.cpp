#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int y,m,d;
    bool f=false;
    cin>>y>>m;
    if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
        d=31;
    if(m==4||m==6||m==9||m==11)
        d=30;
    if(y%4==0)
        f=true;
    if(y%100==0)
        f=false;
    if(y%400==0)
        f=true;
    if(m==2)
    {
        if(f==true)
            d=29;
        else
            d=28;
    }
    cout<<d<<endl;
}
