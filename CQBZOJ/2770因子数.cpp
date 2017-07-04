#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int n,count=0;
	cin>>n;
	for(int i=1;i<=sqrt(n);i++)
		if(n%i==0)
		{
			count+=2;
			if(i*i==n)
				count--;
		}
	cout<<count<<endl;
	return 0;
}
