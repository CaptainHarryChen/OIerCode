#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		if(i==1)
			continue;
		m=0;
		for(int j=1;j<=i/2;j++)
			if(i%j==0)
				m+=j;
		if(m==i)
			cout<<i<<endl;
	}
}
