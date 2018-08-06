#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=23,MAXL1=18,MAXK=1005,MAXCHAR=3;

struct Node
{
	bool vis;
	int dp[MAXK];
	int cnt;
	Node *son[MAXCHAR],*fail;
};

Node nodes[MAXN*MAXL1],*root,*ntop;
void Init()
{
	memset(nodes,0,sizeof nodes);
	root=nodes;
	ntop=nodes+1;
}
void Insert(const char *str)
{
	Node *u=root;
	for(int i=0;str[i];i++)
	{
		int c=str[i]-'A';
		if(u->son[c]==NULL)
		{
			u->son[c]=ntop++;
			memset(u->son[c]->dp,0x80,sizeof u->son[c]->dp);
		}
		u=u->son[c];
	}
	u->cnt++;
}
void Build()
{
	static queue<Node*> Q;
	for(int i=0;i<MAXCHAR;i++)
		if(root->son[i])
		{
			root->son[i]->fail=root;
			Q.push(root->son[i]);
		}
	root->dp[0]=0;

	while(!Q.empty())
	{
		Node *u=Q.front();
		Q.pop();
		for(int i=0;i<MAXCHAR;i++)
			if(u->son[i])
			{
				Node *v=u->son[i],*f=u->fail;
				Q.push(v);
				while(f!=root&&f->son[i]==NULL)
					f=f->fail;
				if(f->son[i])
					v->fail=f->son[i];
				else
					v->fail=root;
				v->cnt+=v->fail->cnt;
			}
	}
}

char A[MAXL1];
queue<Node*> Q;

int main()
{
	Init();
	int N,K;
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%s",A);
		Insert(A);
	}
	Build();
	for(int i=1;i<=K;i++)
	{
		Q.push(root);
		while(!Q.empty())
		{
			Node *u=Q.front();
			Q.pop();
			for(int c=0;c<MAXCHAR;c++)
				if(u->son[c])
				{
					Node *v=u->son[c];
					v->dp[i]=max(v->dp[i],u->dp[i-1]+v->cnt);
					Q.push(v);
				}
			for(Node *tmp=u->fail;tmp;tmp=tmp->fail)
				tmp->dp[i]=max(tmp->dp[i],u->dp[i]);
		}
	}
	printf("%d\n",root->dp[K]);
	
	return 0;
}