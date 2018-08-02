#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20005;

struct Node
{
	int len,minpos;
	Node *fail,*son[26];
};

bool Pnodecmp(Node *a,Node *b)
{return a->len>b->len;}

Node nodes[MAXN*2],*root,*ntop,*last,*st[MAXN*2];
int ncnt;

void Init()
{
	memset(nodes,0,sizeof nodes);
	memset(st,0,sizeof st);
	last=root=nodes;
	ntop=nodes+1;
	st[ncnt=1]=root;
}
void Extend(int ch)
{
	Node *p=last,*np=ntop++;
	st[++ncnt]=np;
	np->len=last->len+1;
	np->minpos=np->len;
	for(;p&&p->son[ch]==NULL;p=p->fail)
		p->son[ch]=np;
	if(p==NULL)
		np->fail=root;
	else
	{
		Node *q=p->son[ch];
		if(q->len==p->len+1)
			np->fail=q;
		else
		{
			Node *nq=ntop++;
			st[++ncnt]=nq;
			*nq=*q;
			nq->len=p->len+1;
			for(;p&&p->son[ch]==q;p=p->fail)
				p->son[ch]=nq;
			q->fail=np->fail=nq;
		}
	}
	last=np;
}
void Build(const char *str)
{
	Init();
	for(int i=0;str[i];i++)
		Extend(str[i]-'a');
	sort(st+1,st+ncnt+1);
	for(int i=1;i<=ncnt;i++)
		if(st[i]->fail)
			st[i]->fail->minpos=min(st[i]->fail->minpos,st[i]->minpos);
}
int Solve(int n)
{
	Node *u=root;
	for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++)
			if(u->son[j])
			{
				u=u->son[j];
				break;
			}
	return u->minpos-n;
}

int T,n;
char str[MAXN];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",str);
		n=strlen(str);
		for(int i=0;i<n-1;i++)
			str[i+n]=str[i];
		str[n*2-1]=0;
		Build(str);
		printf("%d\n",Solve(n)+1);
	}
	return 0;
}
