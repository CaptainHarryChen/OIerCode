#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
int a[10][10];
using namespace std;
int main()
{
	int n;
	cin>>n;
	int i=0,j=n-1;
	for(int k=65,f=0;k<=n*n+64;k++)
	{
		a[i][j]=k;
		if((f%4==0&&(a[i+1][j]!=0||i+1>=n))||(f%4==1&&(a[i][j-1]!=0||j-1<0))||(f%4==2&&(i-1<0||a[i-1][j]!=0))||(f%4==3&&(j+1>=n||a[i][j+1]!=0)))
			f++;
		switch(f%4)
		{
			case 0:i++;break;
			case 1:j--;break;
			case 2:i--;break;
			case 3:j++;break;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(j==0)
				printf("%c",a[i][j]);
			else
				printf(" %c",a[i][j]);
		}
		cout<<endl;
	}
	return 0;
}
