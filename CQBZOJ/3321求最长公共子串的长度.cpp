#include<cstdio>
#include<cstring>
#define MAXN 250005
#define max(a,b) (a>b?a:b)
char S1[MAXN],S2[MAXN];
namespace SuffixAutomaton
{
	struct Node
	{
		Node *son[26],*per;
		int step;
		Node():per(NULL),step(0){memset(son,0,sizeof son);}
	}_new[MAXN<<1],*cur=_new,*root=cur++,*last=cur-1;
	int Extend(int x)
	{
		Node *p=last,*np=cur++;
		np->step=p->step+1;
		while(p&&!p->son[x])
		{
			p->son[x]=np;
			p=p->per;
		}
		if(!p)
			np->per=root;
		else
		{
			Node *q=p->son[x];
			if(p->step+1==q->step)
				np->per=q;
			else
			{
				Node *nq=cur++;
				memcpy(nq->son,q->son,sizeof q->son);
				nq->step=p->step+1;
				nq->per=q->per;
				q->per=np->per=nq;
				while(p&&p->son[x]==q)
				{
					p->son[x]=nq;
					p=p->per;
				}
			}
		}
		last=np;
		return 1;
	}
}
int main()
{
	scanf("%s%s",S1,S2);
	for(int i=0;S1[i];i++)
	{
		if(!SuffixAutomaton::Extend(S1[i]-'a'))
			printf("%d:ERROR\n",i);
	}
	SuffixAutomaton::Node *t=SuffixAutomaton::root;
	int len=0,ans=0;
	for(int i=0,x;S2[i];i++)
	{
		x=S2[i]-'a';
		if(t->son[x])
		{
			t=t->son[x];
			len++;
		}
		else
		{
			while(t&&!t->son[x])
				t=t->per;
			if(!t)
			{len=0;t=SuffixAutomaton::root;}
			else
			{
				len=t->step+1;
				t=t->son[x];
			}
		}
		ans=max(ans,len);
	}
	printf("%d\n",ans);
	return 0;
}
