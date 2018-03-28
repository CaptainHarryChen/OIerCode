#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=30,MAXS=4100,MAXHASH=99983;

namespace Hash
{
	struct Node
	{
		int id;
		int num,plan;
		Node *nxt;
	};
	Node node[MAXS],*_new=node,*adj[MAXHASH];
	void Set(int id,int num,int plan)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
			{
				p->num=num;p->plan=plan;
				return;
			}
		_new->id=id;
		_new->num=num;_new->plan=plan;
		_new->nxt=adj[pos];
		adj[pos]=_new++;
	}
	pair<int,int> Get(int id)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
				return make_pair(p->num,p->plan);
		return make_pair(-1,-1);
	}
}

char str[MAXN][MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%s",str[i]);
	for(int s=0;s<1<<(n/2);s++)
	{
		int p=0,b=__builtin_popcount(s);
		for(int i=0;i<n/2;i++)
			if(s&(1<<i))
				for(int j=0;str[i][j];j++)
					p^=(1<<(str[i][j]-'A'));
		pair<int,int> t=Hash::Get(p);
		if(t.first<b)
			Hash::Set(p,b,s);
	}
	int ans=0,best=0;
	for(int s=0;s<1<<((n+1)/2);s++)
	{
		int p=0,b=__builtin_popcount(s);
		for(int i=n/2;i<n;i++)
			if(s&(1<<(i-n/2)))
				for(int j=0;str[i][j];j++)
					p^=(1<<(str[i][j]-'A'));
		pair<int,int> t=Hash::Get(p);
		if(t.first!=-1)
			if(ans<b+t.first)
				ans=b+t.first,best=t.second^(s<<(n/2));
	}
	printf("%d\n",ans);
	for(int i=0,j=1;j<=ans;i++)
		if(best&(1<<i))
			printf("%d%c",i+1,j==ans?'\n':' '),j++;
	return 0;
}
