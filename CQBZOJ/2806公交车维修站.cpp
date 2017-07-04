#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
stack<string> bus;
int main()
{
	string s;
	int m;
	cin>>m;
	char e[5];
	for(int i=0;i<m;i++)
	{
		scanf("%s",e);
		if(strcmp(e,"out")==0)
			bus.pop();
		else
		{
			cin>>s;
			bus.push(s);
		}
	}
	while(!bus.empty())
	{
		cout<<bus.top()<<endl;
		bus.pop();
	}
	return 0;
}
