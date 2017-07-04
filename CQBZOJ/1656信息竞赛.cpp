#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int i,s=0,n,m,k;
	cin>>n>>m>>k;
	for(i=1;2*i+i<=m+n-k;i++)
		if(2*i<=n&&i<=m)
			s=i;
	cout<<s<<endl;
	return 0;
}

