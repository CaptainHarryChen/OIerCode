#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int a[10010];
int main()
{
	int n,cnt=0;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cnt=0;
		for(int j=1;j*j<=i+1;j++)
		{
			if((i+1)%j==0)
				cnt+=2;
			if(j*j==i+1)
				cnt--;
		}
		a[i]=cnt;
	}
	for(int i=0;i<n;i++)
		cout<<a[i]<<endl;
	return 0;
}
