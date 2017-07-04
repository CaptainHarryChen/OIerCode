#include<cstdio>
#include<iostream>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
queue<string>p;
stack<string>buy;
int main()
{
	int n,m;
	string name;
	char s[10];
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>name;
		p.push(name);
	}
	for(int i=0;i<m;i++)
	{
		scanf("%s",s);
		if(strcmp(s,"buy")==0)
		{buy.push(p.front());p.pop();}
		else if(strcmp(s,"new")==0)
		{
			cin>>name;
			p.push(name);
		}
		else if(strcmp(s,"back")==0)
		{
			p.push(buy.top());
			buy.pop();
		}
	}
	while(!p.empty())
	{
		cout<<p.front()<<endl;
		p.pop();
	}
	return 0;
}
