#include<cstring>
#include<cstdio>
#include<queue>
using std::queue;
#define MAXN 10005
#define MAXWORD 55
#define MAXLEN 1000005
#define MAX_NODES MAXN*MAXWORD
#define MAX_CHAR 26
namespace AC
{
	char _ch;
	int root,top;
	queue<int>Q;
	struct Node
	{
		int son[MAX_CHAR],fail,cnt;
	}nodes[MAX_NODES];
	void Init(char a)
	{
		root=0;top=0;_ch=a;
		memset(nodes,0,sizeof nodes);
		while(!Q.empty())Q.pop();
	}
	void Insert(char *s)
	{
		int len=strlen(s),u=root,x;
		for(int i=0;i<len;i++)
		{
			x=s[i]-_ch;
			if(!nodes[u].son[x])
			{nodes[u].son[x]=++top;}
			u=nodes[u].son[x];
		}
		nodes[u].cnt++;
	}
	void Build()
	{
		for(int i=0;i<MAX_CHAR;i++)
			if(nodes[root].son[i])
				Q.push(nodes[root].son[i]);
		int u,v,f;
		while(!Q.empty())
		{
			u=Q.front();Q.pop();
			for(int i=0;i<MAX_CHAR;i++)
				if(nodes[u].son[i])
				{
					v=nodes[u].son[i];
					Q.push(v);
					f=nodes[u].fail;
					while(f&&!nodes[f].son[i])f=nodes[f].fail;
					if(nodes[f].son[i])
						nodes[v].fail=nodes[f].son[i];
				}
		}
	}
	bool vis[MAX_NODES];
	int Match(char *s)
	{
		memset(vis,0,sizeof vis);
		int ret=0,u=root,x,temp;
		int len=strlen(s);
		for(int i=0;i<len;i++)
		{
			x=s[i]-'a';
			while(u!=root&&!nodes[u].son[x])
				u=nodes[u].fail;
			if(nodes[u].son[x])
			{
				u=nodes[u].son[x];
				for(temp=u;temp!=root;temp=nodes[temp].fail)
				{
					if(vis[temp])break;
					ret+=nodes[temp].cnt;
					vis[temp]=1;
				}
			}
		}
		return ret;
	}
}
char str[MAXLEN];
int main()
{
	int test,n;
	scanf("%d",&test);
	using namespace AC;
	while(test--)
	{
		Init('a');
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			Insert(str);
		}
		Build();
		scanf("%s",str);
		printf("%d\n",Match(str));
	}
	return 0;
}
