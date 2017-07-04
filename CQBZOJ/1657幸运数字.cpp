#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
bool f(int i)
{
	char s[10];
	sprintf(s,"%d",i);
	int len=strlen(s);
	for(int j=0;j<len;j++)
		if(s[j]!='4'&&s[j]!='7')
			return 0;
	return 1;
}
int main()
{
	int n,i;
	cin>>n;
	for(i=0;n;i++)
		if(f(i))
			n--;
	cout<<i-1<<endl;
	return 0;
}
