#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=50005;
struct SegTree
{
	int Max[MAXN<<2],Min[MAXN<<2];
	void Insert(int id,int pos,int val,int l,int r)
	{
		if(r<pos||l>pos)
			return;
		if(l==r)
		{
			Max[id]=Min[id]=val;
			return;
		}
		Insert(id*2,pos,val,l,(l+r)/2);
		Insert(id*2+1,pos,val,(l+r)/2+1,r);
		Max[id]=max(Max[id*2],Max[id*2+1]);
		Min[id]=min(Min[id*2],Min[id*2+1]);
	}
	int GetMax(int id,int L,int R,int l,int r)
	{
		if(r<L||l>R)
			return 0;
		if(L<=l&&r<=R)
			return Max[id];
		int ret=0;
		ret=max(ret,GetMax(id*2,L,R,l,(l+r)/2));
		ret=max(ret,GetMax(id*2+1,L,R,(l+r)/2+1,r));
		return ret;
	}
	int GetMin(int id,int L,int R,int l,int r)
	{
		if(r<L||l>R)
			return 0x7FFFFFFF;
		if(L<=l&&r<=R)
			return Min[id];
		int ret=0x7FFFFFFF;
		ret=min(ret,GetMin(id*2,L,R,l,(l+r)/2));
		ret=min(ret,GetMin(id*2+1,L,R,(l+r)/2+1,r));
		return ret;
	}
};
SegTree T;
int main()
{
	int N,Q;
	scanf("%d%d",&N,&Q);
	for(int i=1,x;i<=N;i++)
	{
		scanf("%d",&x);
		T.Insert(1,i,x,1,N);
	}
	for(int i=1,x,y;i<=Q;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",T.GetMax(1,x,y,1,N)-T.GetMin(1,x,y,1,N));
	}
	return 0;
}
