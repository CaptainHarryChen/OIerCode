#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXL=1000005;

struct Node
{
	int mx;
	Node *son[30],*pre;
}nodes[MAXL*2],*ncur=nodes+1,*root=nodes,*last=root;
void Insert(int c)
{
	Node *p=last,*np=ncur++;
	np->mx=last->mx+1;
	for(;p&&p->son[c]==NULL;p=p->pre)
		p->son[c]=np;
	if(p==NULL)
		np->pre=root;
	else
	{
		Node *q=p->son[c];
		if(q->mx==p->mx+1)
			np->pre=q;
		else
		{
			Node *nq=ncur++;
			memcpy(nq,q,sizeof(Node));
			nq->mx=p->mx+1;
			q->pre=np->pre=nq;
			for(;p&&p->son[c]==q;p=p->pre)
				p->son[c]=nq;
		}
	}
	last=np;
}

char str[MAXL],q[MAXL];

int main()
{
	int n;
	scanf("%s",str);
	n=strlen(str);
	for(int i=0;i<n;i++)
		Insert(str[i]-'a');
	long long ans=0;
	for(Node *it=nodes+1;it!=ncur;it++)
		ans+=1LL*(it->mx-it->pre->mx);
	printf("%lld\n",ans);
	return 0;
}
