#include<iostream>
#include<cstdio>
using namespace std;
char s[1000];
int a[30];
int main()
{
	int n,cnt=0;
	cin>>n;
	for(int i=0;i<=n;i++)
	{
		scanf("%c",&s[i]);
		if(s[i]>='A'&&s[i]<='Z')
			a[s[i]-'A']++;
	}
	for(int i=0;i<26;i++)
		if(a[i])
			cnt++;
	cout<<cnt<<endl;
	return 0;
}
