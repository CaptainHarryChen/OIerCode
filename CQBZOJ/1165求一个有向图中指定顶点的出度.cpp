#include<cstdio>
#include<iostream>
using namespace std;
int a[20005][2];
int main()
{
	int n,m,k,s=0;
	cin>>n>>m;
	for(int i=0;i<m;i++)
		scanf("%d%d",&a[i][0],&a[i][1]);
	cin>>k;
	for(int i=0;i<m;i++)
		if(a[i][0]==k)
			s++;
	cout<<s<<endl;
	return 0;
}
