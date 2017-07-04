#include<cstdio>
#include<iostream>
using namespace std;
int f[3000];
int main()
{
	int i,j,n;
	cin>>n;
	f[0]=1;
	for(i=2;i<=n;i++)
	{
		int c=0;
		for(j=0;j<3000;j++)
		{
			int s=f[j]*i+c;
			f[j]=s%10;
			c=s/10;
		}
	}
	for(j=3000-1;j>=0;j--) 
		if(f[j]) 
			break;
	for(i=j;i>=0;i--) 
		cout<<f[i];
	cout<<endl;
	return 0;
}
