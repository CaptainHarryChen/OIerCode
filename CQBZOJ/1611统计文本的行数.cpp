#include <iostream>
#include<cstdio>
using namespace std;
char s[100000];
int main()
{
	int cnt=0,i=0;
	while(scanf("%c",&s[i])==1)
	{
		if(s[i]=='\n')
			cnt++;
		i++;
	}
	cout<<cnt<<endl;
	return 0;
}
