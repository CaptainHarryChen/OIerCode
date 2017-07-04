#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a,b,c;
bool year(int y)
{
    bool f;
    if((y%4==0)&&(y%100!=0))
        f=true;
    else if(y%400==0)
        f=true;
    else
        f=false;
    return f;
}
 
int moon(int m)
{
    int d;
    switch(m)
    {
        case 2:d=1;break;
        case 4:d=30;break;
        case 6:d=30;break;
        case 9:d=30;break;
        case 11:d=30;break;
        default:d=31;break;
    }
    if(d==1&&year(a)==true)
        d=29;
    else if(d==1)
        d=28;
    return d;
}
 
int main()
{int n;
    cin>>a>>b>>c;
    n=c;
    c=c+1;
    if(c>28&&moon(b)<c){b++;c=moon(b-1)-n+1;}
    if(b>12){a++;b=1;}
    cout<<a<<' '<<b<<' '<<c<<endl;
    return 0;
}