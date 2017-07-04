#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	char s[5];
	int n;
	cin>>s;
	n=strlen(s);
	cout<<n<<endl;
	for(int i=n-1;i>=0;i--)
		cout<<s[i];
	cout<<endl;
}
