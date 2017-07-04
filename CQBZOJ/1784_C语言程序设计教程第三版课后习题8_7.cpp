#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s[1005];
using namespace std;
int main()
{
	gets(s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')
			cout<<s[i];
	cout<<endl;
	return 0;
}
