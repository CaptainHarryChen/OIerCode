#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXCHAR=30;

struct Node
{
	int len,ans,now;
	Node *son[MAXCHAR],*fail;
};

bool Nodecmp(Node *a,Node *b)
{return a->len>b->len;}

Node nodes[MAXN*2],*root,*last,*ntop;
Node *st[MAXN*2];
int ncnt;
void Init()
{
	memset(nodes,0,sizeof nodes);
	ntop=nodes+1;
	last=root=nodes;
}
void Extend(int ch)
{
	Node *p=last,*np=ntop++;
	np->ans=0x7FFFFFFF;
	np->len=last->len+1;
	for(;p&&p->son[ch]==NULL;p=p->fail)
		p->son[ch]=np;
	if(p)
	{
		Node *q=p->son[ch];
		if(q->len==p->len+1)
			np->fail=q;
		else
		{
			Node *nq=ntop++;
			*nq=*q;
			nq->len=p->len+1;
			for(;p&&p->son[ch]==q;p=p->fail)
				p->son[ch]=nq;
			q->fail=nq;
			np->fail=nq;
		}
	}
	else
		np->fail=root;
	last=np;
}
void Build(const char *str)
{
	Init();
	for(int i=0;str[i];i++)
		Extend(str[i]-'a');
	ncnt=0;
	for(Node *p=nodes;p<ntop;p++)
		st[++ncnt]=p;
	sort(st+1,st+ncnt+1,Nodecmp);
}
void Match(const char *tmp)
{
	Node *u=root;
	int ans=0;
	for(int i=0;tmp[i];i++)
	{
		int ch=tmp[i]-'a';
		while(u&&u->son[ch]==NULL)
			u=u->fail;
		if(!u)
		{
			u=root;
			ans=0;
		}
		else
		{
			ans=min(ans,u->len);
			ans++;
			u=u->son[ch];
		}
		u->now=max(u->now,ans);
	}
	for(int i=1;i<=ncnt;i++)
	{
		st[i]->ans=min(st[i]->ans,st[i]->now);
		if(st[i]->fail)
			st[i]->fail->now=max(st[i]->fail->now,min(st[i]->fail->len,st[i]->now));
		st[i]->now=0;
	}
}

char S[MAXN];

int main()
{
	scanf("%s",S);
	Build(S);
	while(scanf("%s",S)!=EOF)
		Match(S);
	int ans=0;
	for(int i=1;i<=ncnt;i++)
		ans=max(ans,st[i]->ans);
	printf("%d\n",ans);
	
	return 0;
}
