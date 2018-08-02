#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=90005;

struct Node
{
	int cnt,len;
	Node *fail,*son[26];
};

bool Pnodecmp(Node *a,Node *b)
{return a->len>b->len;}

Node nodes[MAXN*2],*root,*last,*ntop,*st[MAXN*2];
int ncnt;

void Init()
{
	root=last=nodes;
	ntop=nodes+1;
	st[ncnt=1]=root;
}
void Extend(int ch)
{
	Node *p=last,*np=ntop++;
	st[++ncnt]=np;
	np->len=last->len+1;
	np->cnt=1;
	for(;p&&p->son[ch]==NULL;p=p->fail)
		p->son[ch]=np;
	if(!p)
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
	sort(st+1,st+ncnt+1,Pnodecmp);
	for(int i=1;i<=ncnt;i++)
		for(int j=0;j<26;j++)
			if(st[i]->son[j])
				st[i]->cnt+=st[i]->son[j]->cnt;
}

void Solve(int K)
{
	Node *u=root;
	long long sum=0;
	while(sum<K)
	{
		int i;
		for(i=0;i<26;i++)
			if(u->son[i])
			{
				if(sum+u->son[i]->cnt<K)
					sum+=u->son[i]->cnt;
				else
					break;
			}
		putchar(i+'a');
		sum++;
		u=u->son[i];
	}
	putchar('\n');
}

int Q,K;
char str[MAXN];

int main()
{
	scanf("%s",str);
	Build(str);
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&K);
		Solve(K);
	}
	
	return 0;
}
