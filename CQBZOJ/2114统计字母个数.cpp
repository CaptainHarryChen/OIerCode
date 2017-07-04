#include<iostream>
#include<cstdio>
using namespace std;
char s[1000];
int a[10];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
		if(s[i]>='0'&&s[i]<='9')
			a[s[i]-'0']++;
	}
	for(int i=0;i<10;i++)
		cout<<i<<' '<<a[i]<<endl;
	return 0;
}
