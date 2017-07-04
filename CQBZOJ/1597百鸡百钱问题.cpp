#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
    int a,b,c,x,y;
	cin>>x>>y;
    for (a=0;a<=3000;a++)
        for (b=0;b<=3000;b++)
		{
			c=y-a-b;
			if ((a+b+c==y)&&(5*a+3*b+c/3==x)&&(c%3==0)&&(c>=0))
			{
				cout<<a<<' '<<b<<' '<<c<<endl;
				return 0;
			}
		}
	cout<<"NO SOLUTION"<<endl;
	return 0;
}
