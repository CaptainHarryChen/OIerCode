#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;
int main()
{
	int a,b,c,i;
	cin>>a>>b>>c;
	i=a;
	if(i<b)
		i=b;
	if(i<c)
		i=c;
	cout<<i<<endl;
}
