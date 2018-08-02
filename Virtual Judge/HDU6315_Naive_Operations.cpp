#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n,m,b[MAXN];

struct Node
{
	int maxa,minb;
	int add,ans;
}node[MAXN*4];

void PushUp(int id)
{
	node[id].maxa=max(node[(id<<1)].maxa,node[(id<<1)|1].maxa);
	node[id].minb=min(node[(id<<1)].minb,node[(id<<1)|1].minb);
	node[id].ans=node[(id<<1)].ans+node[(id<<1)|1].ans;
}
void PushDown(int id)
{
	if(node[id].add)
	{
		int &v=node[id].add;
		node[(id<<1)].add+=v;
		node[(id<<1)].maxa+=v;
		node[(id<<1)|1].add+=v;
		node[(id<<1)|1].maxa+=v;
		v=0;
	}
}
void Build(int l=1,int r=n,int id=1)
{
	node[id].add=node[id].ans=node[id].maxa=0;
	if(l==r)
	{
		node[id].minb=b[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(l,mid,(id<<1));
	Build(mid+1,r,(id<<1)|1);
	PushUp(id);
}
void Add(int L,int R,int l=1,int r=n,int id=1)
{
	if(L<=l&&r<=R)
	{
		node[id].maxa++;
		if(node[id].maxa<node[id].minb)
		{
			node[id].add++;
			return;
		}
		if(l==r&&node[id].maxa>=node[id].minb)
		{
			node[id].ans++;
			node[id].minb+=b[l];
			return;
		}
	}
	int mid=(l+r)>>1;
	PushDown(id);
	if(L<=mid)
		Add(L,R,l,mid,(id<<1));
	if(mid<R)
		Add(L,R,mid+1,r,(id<<1)|1);
	PushUp(id);
}
int Query(int L,int R,int l=1,int r=n,int id=1)
{
	if(L<=l&&r<=R)
		return node[id].ans;
	int res=0,mid=(l+r)>>1;
	PushDown(id);
	if(L<=mid)
		res+=Query(L,R,l,mid,(id<<1));
	if(mid<R)
		res+=Query(L,R,mid+1,r,(id<<1)|1);
	return res;
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		
		Build();
		char op[10];
		int x,y;
		for(int i=1;i<=m;i++)
		{
			scanf("%s%d%d",op,&x,&y);
			if(op[0]=='q')
				printf("%d\n",Query(x,y));
			else
				Add(x,y);
		}
	}
	
	return 0;
}
