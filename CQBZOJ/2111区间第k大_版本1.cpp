#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#define MAXN 100100
using namespace std;
map<int,int>Map;
int N,M,num[MAXN],map1[MAXN];
struct TREE
{
	int cnt;
	TREE *lch,*rch;
	TREE(){cnt=0;lch=rch=NULL;}
	TREE(int L,int R){cnt=R-L+1;lch=rch=NULL;}
}*root[MAXN];
void build_tree(TREE *&p,int L,int R)
{
	p=new TREE(L,R);
	if(L==R)return;
	int mid=(L+R)>>1;
	build_tree(p->lch,L,mid);
	build_tree(p->rch,mid+1,R);
}
void insert(TREE *&u,TREE *v,int L,int R,int x)
{
	u=new TREE;
	*u=*v;
	u->cnt++;
	if(L==R)return;
	int mid=(L+R)>>1;
	if(x<=mid)insert(u->lch,v->lch,L,mid,x);
	else insert(u->rch,v->rch,mid+1,R,x);
}
int solve(TREE *u,TREE *v,int L,int R,int k)
{
	if(L==R)return L;
	int c=(u->lch->cnt)-(v->lch->cnt),mid=(L+R)>>1;
	if(k<=c)
		return solve(u->lch,v->lch,L,mid,k);
	else
		return solve(u->rch,v->rch,mid+1,R,k-c);
}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		scanf("%d",&num[i]);
	memcpy(map1,num,sizeof map1);
	sort(map1+1,map1+N+1);
	for(int i=1;i<=N;i++)
		Map[map1[i]]=i;
	build_tree(root[0],1,N);
	for(int i=1;i<=N;i++)
	{
		int x=Map[num[i]];
		insert(root[i],root[i-1],1,N,x);
	}
	int l,r,k;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		int S=solve(root[r],root[l-1],1,N,k);
		printf("%d\n",map1[S]);
	}
	return 0;
}
