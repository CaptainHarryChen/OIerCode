#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[105][105];
int main()
{
	int n,b,c,d,s,m;
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	b=c=d=99999999;
	for(int i=0;i<n;i++)
	{
		s=0;
		for(int j=0;j<n;j++)
			s+=a[i][j];
		if(b>=s)
			b=s;
	}
	for(int j=0;j<n;j++)
	{
		s=0;
		for(int i=0;i<n;i++)
			s+=a[i][j];
		if(c>=s)
			c=s;
	}
	s=0;
	for(int i=0;i<n;i++)
		s+=a[i][i];
	if(d>=s)
		d=s;
	s=0;
	for(int i=0;i<n;i++)
		s+=a[i][n-i-1];
	if(d>=s)
		d=s;
	m=b;
	if(m>c)m=c;
	else if(m>d)m=d;
	cout<<m<<endl;
	if(m==b)
		cout<<"ROW"<<endl;
	if(m==c)
		cout<<"COL"<<endl;
	if(m==d)
		cout<<"DIA"<<endl;
	return 0;
}
