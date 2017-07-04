#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int n,m;
	char s[6]={0};
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		if(i%7==0)
		{
			cout<<i<<endl;
			continue;
		}
		sprintf(s,"%d",i);
		m=strlen(s);
		for(int j=0;j<m;j++)
			if(s[j]=='7')
			{
				cout<<i<<endl;
				break;
			}
	}
	return 0;
}
