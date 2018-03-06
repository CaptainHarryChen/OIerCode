#include<cstdio>
#include<stack>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,q;

namespace SegTree
{
	int sum[MAXN*4];
	bool zero[MAXN*4];
	void PushUp(int id)
	{
		sum[id]=sum[id*2]+sum[id*2+1];
		if(sum[id])zero[id]=false;
	}
	void PushDown(int id)
	{
		if(zero[id])
		{
			zero[id*2]=zero[id*2+1]=true;
			sum[id*2]=sum[id*2+1]=0;
		}
	}
	void Modify(int pos,int val,int L=1,int R=n,int id=1)
	{
		if(L==pos&&pos==R)
		{
			sum[id]=val;
			return;
		}
		int mid=(L+R)/2;
		if(pos<=mid)
			Modify(pos,val,L,mid,id*2);
		else
			Modify(pos,val,mid+1,R,id*2+1);
		PushUp(id);
	}
	void Clear(int l,int r,int L=1,int R=n,int id=1)
	{
		if(l>r)return;
		if(l<=L&&R<=r)
		{
			zero[id]=true;
			sum[id]=0;
			return;
		}
		int mid=(L+R)/2;
		if(l<=mid)
			Clear(l,r,L,mid,id*2);
		if(mid<r)
			Clear(l,r,mid+1,R,id*2+1);
		PushUp(id);
	}
	int Sum(int l,int r,int L=1,int R=n,int id=1)
	{
		if(l>r)return 0;
		if(l<=L&&R<=r)
			return sum[id];
		int mid=(L+R)/2,ret=0;
		PushDown(id);
		if(l<=mid)
			ret+=Sum(l,r,L,mid,id*2);
		if(mid<r)
			ret+=Sum(l,r,mid+1,R,id*2+1);
		return ret;
	}
}

namespace UFset
{
	int fa[MAXN];
	int root(int x)
	{
		if(fa[x]==0)
			return x;
		fa[x]=root(fa[x]);
		return fa[x];
	}
	void Union(int x,int y)
	{fa[y]=x;}
}

struct query
{
	int l,r,id;
}que[MAXN];
bool cmp(query a,query b)
{return a.l>b.l||(a.l==b.l&&a.r<b.r);}

pair<int,int> domi[MAXN];
stack<int> stk;
int ans[MAXN];

void solve()
{
	int l=n,r=n;
	stk.push(n);
	for(int i=1;i<=q;i++)
	{
		while(l>que[i].l)
		{
			l--;
			int far=domi[l].first+domi[l].second,x;
			while(!stk.empty())
			{
				x=stk.top();
				if(domi[x].first>far)
					break;
				UFset::Union(l,x);
				far=max(far,domi[x].first+domi[x].second);
				stk.pop();
			}
			SegTree::Clear(l+1,x-(domi[x].first>far));
			domi[l].second=far-domi[l].first;
			if(far<domi[x].first)
				SegTree::Modify(l,domi[x].first-far);
			stk.push(l);
		}
		r=UFset::root(que[i].r);
		r--;
		if(l>r)
			ans[que[i].id]=0;
		else
			ans[que[i].id]=SegTree::Sum(l,r);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&domi[i].first,&domi[i].second);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&que[i].l,&que[i].r),que[i].id=i;
		
	sort(que+1,que+q+1,cmp);
	
	solve();
	
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
