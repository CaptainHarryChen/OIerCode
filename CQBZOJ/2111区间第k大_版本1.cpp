#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;

struct Node
{
	int sum;
	Node *lch,*rch;
};

int opcnt;
Node nodes[MAXN*20],*cur,*null;
Node *rt[MAXN];
void Init()
{
    cur=nodes+1;
    nodes[0].sum=0;
    null=nodes;
    nodes[0].lch=nodes[0].rch=null;
    opcnt=0;
    for(int i=0;i<=n;i++)
        rt[i]=null;
}
void Add(Node *&now,int pos,int val,int l=1,int r=n)
{
    *cur=*now;
    now=cur++;
    now->sum+=val;
    if(l==r)return;
    int mid=(l+r)/2;
    if(pos<=mid)
        Add(now->lch,pos,val,l,mid);
    else
        Add(now->rch,pos,val,mid+1,r);
}
int Query(Node *lnode,Node *rnode,int rk,int l=1,int r=n)
{
    if(l==r)
        return l;
    int midrank=(rnode->lch->sum-lnode->lch->sum);
    int mid=(l+r)/2;
    if(rk<=midrank)
        return Query(lnode->lch,rnode->lch,rk,l,mid);
    return Query(lnode->rch,rnode->rch,rk-midrank,mid+1,r);
}

int A[MAXN],mp[MAXN];
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",A+i);
		mp[i]=A[i];
	}
	sort(mp+1,mp+n+1);
	Init();
	for(int i=1;i<=n;i++)
	{
		rt[i]=rt[i-1];
		Add(rt[i],lower_bound(mp+1,mp+n+1,A[i])-mp,1);
	}
	int l,r,k;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",mp[Query(rt[l-1],rt[r],k)]);
	}
	return 0;
}
