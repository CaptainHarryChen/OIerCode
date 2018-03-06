#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXL=1000005;

struct Node
{
	int step,deg,edcnt;
	bool flag;
	Node *pre,*son[30];
}nd[MAXL*2],*ncur=nd+1,*last=nd,*root=nd;
void Insert(int ch)
{
	Node *p=last,*np=ncur++;
	np->step=p->step+1;
	np->flag=true;
	for(;p&&p->son[ch]==NULL;p=p->pre)
		p->son[ch]=np;
	if(p==NULL)
		np->pre=root;
	else
	{
		Node *q=p->son[ch];
		if(q->step==p->step+1)
			np->pre=q;
		else
		{
			Node *nq=ncur++;
			memcpy(nq,q,sizeof(Node));
			nq->step=p->step+1;
			nq->flag=false;
			for(;p&&p->son[ch]==q;p=p->pre)
				p->son[ch]=nq;
			np->pre=q->pre=nq;
		}
	}
	last=np;
}

void calc_edcnt(int n)
{
	static queue<Node*> Q;
	for(Node *p=nd+1;p!=ncur;p++)
		p->pre->deg++;
	for(Node *p=nd;p!=ncur;p++)
		if(p->deg==0)
			Q.push(p);
	while(!Q.empty())
	{
		Node *t=Q.front();
		Q.pop();
		if(t->flag)
			t->edcnt++;
		if(t->pre)
		{
			t->pre->edcnt+=t->edcnt;
			if((--t->pre->deg)==0)
				Q.push(t->pre);
		}
	}
}

char str[MAXL];
int ans[MAXL];

int main()
{
	scanf("%s",str);
	int n=strlen(str);
	for(int i=0;i<n;i++)
		Insert(str[i]-'a');
	calc_edcnt(n);
	/*
	for(Node *it=root+1;it!=ncur;it++)
		for(int i=it->pre->step;i<=it->step;i++)
			ans[i]=max(ans[i],it->edcnt);
	*/
	for(Node *it=root+1;it!=ncur;it++)
		ans[it->step]=max(ans[it->step],it->edcnt);
	for(int i=n-1;i>0;i--)
		ans[i]=max(ans[i],ans[i+1]);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
