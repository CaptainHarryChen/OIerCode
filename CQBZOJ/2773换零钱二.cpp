#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int n,m,a,b,c,d,count=0;
	cin>>n>>m;
	for(a=1;a<=m;a++)
		for(b=1;b<=m;b++)
			for(c=1;c<=m;c++)
			{
				d=m-a-b-c;
				if(d>0&&a*10+b*5+c*2+d*1==n*100)
					count++;
			}
	cout<<count<<endl;
	return 0;
}
