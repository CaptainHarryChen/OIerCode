#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char n[100];
int main()
{
	int b,m=0,i;
	cin>>b;
	for(i=0;cin>>n[i];i++)
		if(n[i]>='A'&&n[i]<='F')
			n[i]-=7;
	for(int l=i-1,k=1,a=1;l>=0;l--,a++,k=1)
	{
		for(int j=1;j<a;j++)
			k*=b;
		m+=(n[l]-'0')*k;
	}
	cout<<m<<endl;
	return 0;
}
