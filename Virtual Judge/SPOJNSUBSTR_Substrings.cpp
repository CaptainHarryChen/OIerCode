#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=250005,MAXCHAR=30;

struct Node
{
	bool iscopy;
	int len,cnt;
	Node *son[MAXCHAR],*fail;
};

Node nodes[MAXN*2],*root,*last,*ntop;
Node *st[MAXN*2];
int ncnt;

void Init()
{
	memset(nodes,0,sizeof nodes);
	last=root=nodes;
	ntop=nodes+1;
}
void Extend(int ch)
{
	Node *p=last,*np=ntop++;
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
			nq->iscopy=true;
			nq->len=p->len+1;
			np->fail=q->fail=nq;
			for(;p&&p->son[ch]==q;p=p->fail)
				p->son[ch]=nq;
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
	for(Node *i=nodes;i<ntop;i++)
		st[++ncnt]=i;
		
	static int cnt[MAXN*2];
	static Node *tmp[MAXN*2];
	memset(cnt,0,sizeof cnt);
	for(int i=1;i<=ncnt;i++)
		cnt[st[i]->len]++;
	for(int i=1;i<=ncnt;i++)
		cnt[i]+=cnt[i-1];
	for(int i=1;i<=ncnt;i++)
		tmp[cnt[st[i]->len]--]=st[i];
	for(int i=1;i<=ncnt;i++)
		st[i]=tmp[ncnt-i+1];
}

int ans[MAXN],n;
char str[MAXN];
void Solve()
{
	for(int i=1;i<=ncnt;i++)
	{
		if(!st[i]->iscopy)
			st[i]->cnt++;
		if(st[i]->fail)
			st[i]->fail->cnt+=st[i]->cnt;
		ans[st[i]->len]=max(ans[st[i]->len],st[i]->cnt);
	}
	for(int i=n-1;i>=1;i--)
		ans[i]=max(ans[i],ans[i+1]);
}

int main()
{
	scanf("%s",str);
	n=strlen(str);
	Build(str);
	Solve();
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
