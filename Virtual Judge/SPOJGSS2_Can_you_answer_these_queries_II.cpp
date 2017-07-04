#include<cstdio>
#include<algorithm>
const int MAXN=100005,ZERO=100000;
namespace Seg_tree
{
	struct Node
	{
		int ncov,ocov,nmax,omax;
		Node(){ncov=ocov=nmax=omax=0;}
	}nodes[MAXN<<2];
	void Push_down(int id)
	{
		int ls=id<<1,rs=(id<<1)+1;
		
		nodes[ls].ocov=std::max(nodes[ls].ocov,nodes[ls].ncov+nodes[id].ocov);
		nodes[rs].ocov=std::max(nodes[rs].ocov,nodes[rs].ncov+nodes[id].ocov);
		nodes[ls].omax=std::max(nodes[ls].omax,nodes[ls].nmax+nodes[id].ocov);
		nodes[rs].omax=std::max(nodes[rs].omax,nodes[rs].nmax+nodes[id].ocov);
		nodes[ls].nmax+=nodes[id].ncov;
		nodes[rs].nmax+=nodes[id].ncov;
		nodes[ls].ncov+=nodes[id].ncov;
		nodes[rs].ncov+=nodes[id].ncov;
		nodes[id].ncov=nodes[id].ocov=0;
	}
	void Push_up(int id)
	{
		int ls=id<<1,rs=(id<<1)+1;
		nodes[id].nmax=std::max(nodes[ls].nmax,nodes[rs].nmax);
		nodes[id].omax=std::max(nodes[ls].omax,nodes[rs].omax);
	}
	void Add(int id,int nowl,int nowr,int l,int r,int add)
	{
		if(nowl>r||nowr<l)return;
		if(nowl>=l&&nowr<=r)
		{
			nodes[id].ncov+=add;
			nodes[id].ocov=std::max(nodes[id].ocov,nodes[id].ncov);
			nodes[id].nmax+=add;
			nodes[id].omax=std::max(nodes[id].omax,nodes[id].nmax);
			return;
		}
		Push_down(id);
		Add(id<<1,nowl,(nowl+nowr)>>1,l,r,add);
		Add((id<<1)+1,((nowl+nowr)>>1)+1,nowr,l,r,add);
		Push_up(id);
	}
	int Query(int id,int nowl,int nowr,int l,int r)
	{
		if(nowl>r||nowr<l)return -0x7FFFFFFF;
		if(nowl>=l&&nowr<=r)return nodes[id].omax;
		Push_down(id);
		return std::max(Query(id<<1,nowl,(nowl+nowr)>>1,l,r),
		Query((id<<1)+1,((nowl+nowr)>>1)+1,nowr,l,r));
	}
}
int n,sco[MAXN],q;
int pre[MAXN<<1];
struct Question
{
	int l,r,id;
	bool operator < (const Question &t)const
	{return r<t.r;}
}query[MAXN];
int ans[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",sco+i);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&query[i].l,&query[i].r);
		query[i].id=i;
	}
	std::sort(query+1,query+q+1);
	for(int i=1,j=1;i<=n&&j<=q;i++)
	{
		Seg_tree::Add(1,1,n,pre[sco[i]+ZERO]+1,i,sco[i]);
		pre[sco[i]+ZERO]=i;
		while(query[j].r==i)
		{
			ans[query[j].id]=Seg_tree::Query(1,1,n,query[j].l,query[j].r);
			j++;
		}
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
