#include<cstring>
#include<cstdio>
#include<queue>
using std::queue;
using std::max;
#define MAXN 300005
#define MAXM 5005
#define MAX_NODES 4400000
int used[MAXN];
namespace AC
{
	int root,_new;
	struct Node
	{
		int son[26],fail,len;
	}nodes[MAX_NODES];
	void Init()
	{
		memset(nodes,0,sizeof nodes);
		root=1;
		_new=1;
	}
	void Insert(char *s)
	{
		int len=strlen(s),p=root,x;
		for(int i=0;i<len;i++)
		{
			x=s[i]-'a';
			if(!nodes[p].son[x])
			{
				nodes[p].son[x]=++_new;
				nodes[_new].fail=root;
			}
			p=nodes[p].son[x];
		}
		nodes[p].len=max(nodes[p].len,len);
	}
	void Build()
	{
		queue<int>Q;
		for(int i=0;i<26;i++)
			if(nodes[root].son[i])
				Q.push(nodes[root].son[i]);
		int v,f;
		while(!Q.empty())
		{
			int u=Q.front();Q.pop();
			for(int i=0;i<26;i++)
				if(nodes[u].son[i])
				{
					v=nodes[u].son[i];
					Q.push(v);
					f=nodes[u].fail;
					while(f&&!nodes[f].son[i])
						f=nodes[f].fail;
					if(f)
					{
						nodes[v].fail=nodes[f].son[i];
						nodes[v].len=max(nodes[v].len,nodes[nodes[v].fail].len);
					}
				}
		}
	}
	int Match(char *s)
	{
		int ret=0,p=root,x;
		int len=strlen(s);
		for(int i=0;i<len;i++)
		{
			x=s[i]-'a';
			while(p!=root&&!nodes[p].son[x])
				p=nodes[p].fail;
			if(nodes[p].son[x])
			{
				p=nodes[p].son[x];
				used[i-nodes[p].len+1]++;
				used[i+1]--;
			}
		}
		return ret;
	}
}
char S[MAXN],word[MAXM][MAXM];
int n;
int Solve()
{
	int ans=n,temp=0;
	for(int i=0;i<n;i++)
	{
		temp+=used[i];
		if(temp>0)
			ans--;
	}
	return ans;
}
int main()
{
	using namespace AC;
	int m;
	scanf("%d%s%d",&n,S,&m);
	Init();
	for(int i=1;i<=m;i++)
	{
		scanf("%s",word[i]);
		Insert(word[i]);
	}
	Build();
	Match(S);
	printf("%d\n",Solve());
	return 0;
}
