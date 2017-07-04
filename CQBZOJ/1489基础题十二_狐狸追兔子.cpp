#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[10000010];
int main()
{
	int n,m,x=0,cnt=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		x+=i;
		x%=n;
		x=x==0?n:x;
		a[x-1]=1;
	}
	for(int i=0;i<n;i++)
		if(a[i]==0)
			cnt++;
	cout<<cnt<<endl;
	for(int i=0;i<n;i++)
		if(a[i]==0)
			cout<<i+1<<endl;
	return 0;
}
