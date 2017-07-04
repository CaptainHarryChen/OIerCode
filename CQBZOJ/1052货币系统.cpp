#include<cstdio>
#include<iostream>
using namespace std;
long long f[10005];
long long num[30];
int main()
{
	long long v,n;
	cin>>v>>n;
	for(long long i=0;i<v;i++)
		cin>>num[i];
	f[0]=1;
	for(long long i=0;i<v;i++)
		for(long long j=0;j+num[i]<=n;j++)
			f[j+num[i]]=f[j]+f[j+num[i]];
	cout<<f[n]<<endl;
}
