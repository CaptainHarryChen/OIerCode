#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

struct Node *null;
struct Node
{
	int val,siz,dis;
	Node *ch[2];
	void PushUp()
	{
		siz=ch[0]->siz+1+ch[1]->siz;
		dis=ch[1]->dis+1;
	}
};
Node nodes[MAXN],*ntop,*root[MAXN];

void Init()
{
	null=nodes;
	null->val=null->siz=null->dis=0;
	null->ch[0]=null->ch[1]=null;
	ntop=nodes+1;
}
Node *NewNode(int val)
{
	ntop->val=val;
	ntop->siz=1;
	ntop->dis=0;
	ntop->ch[0]=ntop->ch[1]=null;
	return ntop++;
}
Node *Merge(Node *u,Node *v)
{
	if(u==null)
		return v;
	if(v==null)
		return u;
	if(u->val<v->val)
		swap(u,v);
	u->ch[1]=Merge(u->ch[1],v);
	if(u->ch[1]->dis>u->ch[0]->dis)
		swap(u->ch[0],u->ch[1]);
	u->PushUp();
	return u;
}
void Pop(Node *&u)
{
	u=Merge(u->ch[0],u->ch[1]);
}

int t[MAXN];
int pos[MAXN];
int main()
{
	Init();
	int n;
	scanf("%d",&n);
	int cnt=0;
	root[0]=null;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t[i]);
		t[i]-=i;
	}
	for(int i=1;i<=n;i++)
	{
		root[++cnt]=NewNode(t[i]);
		pos[cnt]=i;
		while(cnt>1&&root[cnt]->val<root[cnt-1]->val)
		{
			bool flag=((pos[cnt]-pos[cnt-1])%2==1)&&((pos[cnt-1]-pos[cnt-2])%2==1);
			root[cnt-1]=Merge(root[cnt],root[cnt-1]);
			pos[cnt-1]=pos[cnt];
			if(flag)
				Pop(root[cnt-1]);
			cnt--;
		}
	}
	int last=0;
	long long ans=0;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=last+1;j<=pos[i];j++)
			ans+=1LL*abs(t[j]-root[i]->val);
		last=pos[i];
	}
	printf("%lld\n",ans);
	
	return 0;
}
