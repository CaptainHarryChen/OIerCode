#include<cstdio>
#include<iostream>
using namespace std;
int n,a[105];
int main()
{
	int s=0,m=0;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		s+=a[i];
	}
	s/=n;
	for(int i=0;i<n-1;i++)
	{
		if(a[i]<s)
		{
			m++;
			a[i+1]-=s-a[i];
		}
		else if(a[i]>s)
		{
			m++;
			a[i+1]+=a[i]-s;
		}
	}
	cout<<m<<endl;
	return 0;
}
