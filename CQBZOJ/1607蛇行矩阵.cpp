#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[200][200];
int main()
{
	int n,i=0,j=0;
	cin>>n;
	for(int k=1;k<=(n+1)*n/2;k++)
	{
		a[i][j]=k;
		if(i-1<0)
		{
			for(int b=0;a[b][0]!=0;b++)i=b;
			i++;
			j=0;
		}
		else{i--;j++;}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i;j++)
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

