#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s[100];
int main()
{
	int n,x,a=0;
	cin>>x>>n;
	for(;x;)
	{
		s[a++]=x%n+'0';
		x/=n;
	}
	for(int i=strlen(s)-1;i>=0;i--)
		printf("%c",s[i]);
	cout<<endl;
	return 0;
}
