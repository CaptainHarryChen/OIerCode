#include<cstdio>
const int MAXN=100005;

int N,M;

struct Node *null;
struct Node
{
	long long sum,add;
	Node *ch[2];
};
Node nodes[MAXN*4],*root,*ncnt;

void Init()
{
	null=nodes;
	null->sum=null->add=0;
	null->ch[0]=null->ch[1]=null;
	root=null;
	ncnt=nodes+1;
}
Node *NewNode()
{
	ncnt->sum=ncnt->add=0;
	ncnt->ch[0]=ncnt->ch[1]=null;
	return ncnt++;
}

void PushDown(Node *u,int l,int r)
{
	if(u->ch[0]==null)
		u->ch[0]=NewNode();
	if(u->ch[1]==null)
		u->ch[1]=NewNode();
	int mid=(l+r)/2;
	u->ch[0]->sum+=1LL*(mid-l+1)*u->add;
	u->ch[0]->add+=u->add;
	u->ch[1]->sum+=1LL*(r-mid)*u->add;
	u->ch[1]->add+=u->add;
	u->add=0;
}
void Add(int l,int r,int val,int L=1,int R=N,Node *&u=root)
{
	if(u==null)
		u=NewNode();
	if(l<=L&&R<=r)
	{
		u->sum+=1LL*(R-L+1)*val;
		u->add+=val;
		return;
	}
	PushDown(u,L,R);
	int mid=(L+R)/2;
	if(l<=mid)
		Add(l,r,val,L,mid,u->ch[0]);
	if(mid<r)
		Add(l,r,val,mid+1,R,u->ch[1]);
	u->sum=u->ch[0]->sum+u->ch[1]->sum;
}
long long Query(int l,int r,int L=1,int R=N,Node *u=root)
{
	if((l<=L&&R<=r)||u==null)
		return u->sum;
	PushDown(u,L,R);
	int mid=(L+R)/2;
	long long ans=0;
	if(l<=mid)
		ans+=Query(l,r,L,mid,u->ch[0]);
	if(mid<r)
		ans+=Query(l,r,mid+1,R,u->ch[1]);
	return ans;
}

int main()
{
	int T,op,p,q,v;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		Init();
		for(int i=1;i<=M;i++)
		{
			scanf("%d",&op);
			if(op==0)
			{
				scanf("%d%d%d",&p,&q,&v);
				Add(p,q,v);
			}
			else
			{
				scanf("%d%d",&p,&q);
				printf("%lld\n",Query(p,q));
			}
		}
	}
	
	return 0;
}