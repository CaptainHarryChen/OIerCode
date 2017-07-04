#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[40][40];
int main()
{
	int n;
	cin>>n;
	int i=0,j=n/2;
	a[i][j]=1;
	for(int k=2;k<=n*n;k++)
	{
		while(a[i][j]!=0)
		{
			if((i-1<0&&j+1>=n)||(a[i-1][j+1]!=0))
				i++;
			else
			{
				if(i-1<0)
				{i=n-1;j++;}
				else if(j+1>=n)
				{j=0;i--;}
				else
				{i--;j++;}
			}
		}
		a[i][j]=k;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(j==0)
				cout<<a[i][j];
			else
				cout<<' '<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}
