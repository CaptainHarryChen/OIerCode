#include<iostream>
#include<queue>
#include<cstring>
#define MAXN 105
using namespace std;
int T,level[MAXN],n,m,lcnt[10];
bool check(int x)
{
	for(int i=level[x]+1;i<=9;i++)
		if(lcnt[i]!=0)
			return 0;
	return 1;
}
int main()
{
	cin>>T;
	while(T--)
	{
		memset(lcnt,0,sizeof lcnt);
		queue<int>q;
		cin>>n>>m;
		for(int i=0;i<n;i++)
		{
			cin>>level[i];
			lcnt[level[i]]++;
			q.push(i);
		}
		for(int i=1;;)
		{
			int x=q.front();
			if(check(x))
			{
				if(x==m)
				{cout<<i<<endl;break;}
				lcnt[level[x]]--;
				q.pop();
				i++;
			}
			else
			{
				q.push(x);
				q.pop();
			}
		}
	}
	return 0;
}
