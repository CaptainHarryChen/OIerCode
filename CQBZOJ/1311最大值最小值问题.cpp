#include<cstdio>
#include<iostream>
using namespace std;
int m[10010];
int main()
{
	int n,x,y,a=1,b=1;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>m[i];
	x=m[0];
	y=m[0];
	for(int i=0;i<n;i++)
	{
		if(x<m[i])
		{
			x=m[i];
			a=i+1;
		}
		if(y>m[i])
		{
			y=m[i];
			b=i+1;
		}
	}
	cout<<x<<' '<<a<<endl<<y<<' '<<b<<endl;
	return 0;
}
