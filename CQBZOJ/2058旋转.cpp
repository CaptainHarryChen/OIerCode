#include<cstdio>
#include<iostream>
using namespace std;
char s[1000][1000];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>s[i];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			printf("%c",s[j][n-i-1]);
		cout<<endl;
	}
	return 0;
}
