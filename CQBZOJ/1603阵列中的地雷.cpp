#include<cstdio>
#include<iostream>
using namespace std;
int a[105][105];
int main()
{
	int n,m;
	cin>>m>>n;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			if(a[i][j]>0)
				cout<<i+1<<' '<<j+1<<' '<<a[i][j]<<endl;
	return 0;
}
