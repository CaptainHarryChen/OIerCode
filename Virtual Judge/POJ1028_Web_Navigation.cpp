#include<iostream>
#include<string>
#include<stack>
using namespace std;

stack<string> back,forward;
string op,page,cur;

int main()
{
	cur="http://www.acm.org/";
	for(;;)
	{
		cin>>op;
		if(op=="BACK")
		{
			if(back.empty())
			{
				cout<<"Ignored"<<endl;
				continue;
			}
			forward.push(cur);
			cur=back.top();
			back.pop();
			cout<<cur<<endl;
		}
		if(op=="FORWARD")
		{
			if(forward.empty())
			{
				cout<<"Ignored"<<endl;
				continue;
			}
			back.push(cur);
			cur=forward.top();
			forward.pop();
			cout<<cur<<endl;
		}
		if(op=="VISIT")
		{
			cin>>page;
			while(!forward.empty())
				forward.pop();
			back.push(cur);
			cur=page;
			cout<<cur<<endl;
		}
		if(op=="QUIT")
		{
			break;
		}
	}
	return 0;
}
