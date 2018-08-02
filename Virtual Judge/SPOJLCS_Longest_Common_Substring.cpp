#include<cstdio>
#include<cstring>
const int MAXN=250005,MAXCHAR=30;

struct Node
{
	int len;
	Node *son[MAXCHAR],*pre;
};

Node nodes[MAXN*2],*root,*ntop,*last;

void Init()
{
	memset(nodes,0,sizeof nodes);
	root=nodes;
	ntop=nodes+1;
	last=root;
}
void Insert(int ch)
{
	Node *p=last,*np=ntop++;
	np->len=last->len+1;
	for(;p&&p->son[ch]==NULL;p=p->pre)
		p->son[ch]=np;
	if(p)
	{
		Node *q=p->son[ch];
		if(q->len==p->len+1)
			np->pre=q;
		else
		{
			Node *nq=ntop++;
			*nq=*q;
			nq->len=p->len+1;
			q->pre=nq;
			for(;p&&p->son[ch]==q;p=p->pre)
				p->son[ch]=nq;
			np->pre=nq;
		}
	}
	else
		np->pre=root;
	last=np;
}
void Build(const char *str)
{
	Init();
	for(int i=0;str[i];i++)
		Insert(str[i]-'a');
}
int Match(const char *tmp)
{
	int res=0,len=0;
	Node *u=root;
	for(int i=0;tmp[i];i++)
	{
		int ch=tmp[i]-'a';
		while(u&&u->son[ch]==NULL)
			u=u->pre;
		if(!u)
		{
			len=0;
			u=root;
		}
		else
		{
			if(len>u->len)
				len=u->len;
			len++;
			u=u->son[ch];
		}
		if(res<len)
			res=len;
	}
	return res;
}

char A[MAXN],B[MAXN];

int main()
{
	scanf("%s%s",A,B);
	Build(A);
	printf("%d\n",Match(B));
	
	return 0;
}
