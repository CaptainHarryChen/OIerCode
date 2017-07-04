#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n,i;
	cin>>n;
	for(i=1;n!=1;i++)
	{
		if(n%2==0)
			n/=2;
		else
			n=n*3+1;
	}
	cout<<i-1<<endl;
}
