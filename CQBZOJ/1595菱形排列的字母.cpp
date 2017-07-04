#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n,a=91;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n*2-i*2;j++)
			cout<<' ';
		if(i==1)
			printf("%c\n",--a);
		else
		{
			printf("%c",--a);
			for(int j=1;j<=(i-1)*4-1;j++)
				cout<<' ';
			printf("%c\n",--a);
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=i*2;j++)
			cout<<' ';
		if(i==n-1)
			printf("%c\n",--a);
		else
		{
			printf("%c",--a);
			for(int j=1;j<=n*4-(i+1)*4-1;j++)
				cout<<' ';
			printf("%c\n",--a);
		}
	}
	return 0;
}
