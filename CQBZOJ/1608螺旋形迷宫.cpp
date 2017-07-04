#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[40][40];
int main()
{
	int n,i=0,j=0;
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int k=1,f=0;k<=n*n;k++)
	{
		if(k==n*n){cout<<a[i][j]<<' '<<endl;return 0;}
		cout<<a[i][j]<<' ';
		a[i][j]=0;
		if((f%4==0&&a[i][j+1]==0)||(f%4==1&&a[i+1][j]==0)||(f%4==2&&(j-1<0||a[i][j-1]==0))||(f%4==3&&(i-1<0||a[i-1][j]==0)))
			f++;
		switch(f%4)
		{
			case 0:j++;break;
			case 1:i++;break;
			case 2:j--;break;
			case 3:i--;break;
		}
	}
	return 0;
}
