#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define MAXN 10005
#define MAXM 55
#define MAXLEN 1000005
struct Node
{
	int fail,son[26],cnt;
}Trie[MAXM*MAXN];
int _new=1,root=1;
void Insert(char *s)
{
	int len=strlen(s),x,p=root;
	for(int i=0;i<len;i++)
	{
		x=s[i]-'a';
		if(!Trie[p].son[x])
			Trie[p].son[x]=++_new;
		p=Trie[p].son[x];
		Trie[p].fail=root;
	}
	Trie[p].cnt++;
}
void Build()
{
	queue<int>Q;
	for(int i=0;i<26;i++)
		if(Trie[root].son[i])
			Q.push(Trie[root].son[i]);
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(int i=0;i<26;i++)
			if(Trie[u].son[i])
			{
				int v=Trie[u].son[i];
				Q.push(v);
				int p=Trie[u].fail;
				while(p&&!Trie[p].son[i])p=Trie[p].fail;
				if(!p)continue;
				int t=Trie[p].son[i];
				Trie[v].fail=t;
			}
	}
}
int main()
{
	int test,n,ans,p,len;
	char str[MAXLEN];
	scanf("%d",&test);
	while(test--)
	{
		memset(Trie,0,sizeof Trie);
		_new=1;ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			Insert(str);
		}
		Build();
		scanf("%s",str);
		p=root;
		len=strlen(str);
		for(int i=0,x;i<len;i++)
		{
			x=str[i]-'a';
			while(p!=root&&!Trie[p].son[x])
				p=Trie[p].fail;
			if(Trie[p].son[x])
				p=Trie[p].son[x];
			else p=root;
			for(int temp=p;temp!=root;temp=Trie[temp].fail)
			{
				if(Trie[temp].cnt==-1)break;
				ans+=Trie[temp].cnt;
				Trie[temp].cnt=-1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
