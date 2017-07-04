#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
stack<int>m;
int main()
{
    int n,num,a=1;
	bool f=0;
	cin>>n;
	for(int i=0;i<n;i++,f=0)
	{
		cin>>num;
		for(;a<=n+1;)
		{	
			if(m.empty())
				m.push(a++);
			if(m.top()==num)
			{m.pop();f=1;break;}
			m.push(a++);
		}
		if(!f)
		{printf("NO\n");return 0;}
	}
	printf("YES\n");
    return 0;
}
