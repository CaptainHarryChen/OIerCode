#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s[105];
using namespace std;
int main()
{
	gets(s);
	int len=strlen(s);
	bool f=true;
	for(int i=0;i<=len/2;i++)
		if(s[i]!=s[len-i-1])
			f=false;
	if(f)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
