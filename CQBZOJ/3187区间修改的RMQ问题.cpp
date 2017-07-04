#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 50005
struct NODE
{
	int l,r,mn,mx,lbj;
}tree[MAXN*4];
int _new=1,N,Q,A[MAXN];
void make_tree(int L,int R,int node)
{
	tree[node].l=L,tree[node].r=R;tree[node].lbj=0;
	if(L==R)
	{
		tree[node].mn=tree[node].mx=A[L];
		return;
	}
	int mid=(R+L)/2;
	make_tree(L,mid,node*2);
	make_tree(mid+1,R,node*2+1);
	tree[node].mn=min(tree[node*2].mn,tree[node*2+1].mn);
	tree[node].mx=max(tree[node*2].mx,tree[node*2+1].mx);
}
int mx,mn;
void solve(int node,int l,int r)
{
	if(tree[node].l>r||tree[node].r<l)
		return;
	if(tree[node].l>=l&&tree[node].r<=r)
	{
		mx=max(mx,tree[node].mx+tree[node].lbj);
		mn=min(mn,tree[node].mn+tree[node].lbj);
		return;
	}
	tree[node*2].lbj+=tree[node].lbj;
	tree[node*2+1].lbj+=tree[node].lbj;
	tree[node].mx+=tree[node].lbj;
	tree[node].mn+=tree[node].lbj;
	tree[node].lbj=0;
	solve(node*2,l,r);
	solve(node*2+1,l,r);
}
void add(int L,int R,int v,int node)
{
	if(tree[node].r<L||tree[node].l>R)
		return;
	if(tree[node].l>=L&&tree[node].r<=R)
	{
		tree[node].lbj+=v;
		return;
	}
	tree[node*2].lbj+=tree[node].lbj;
	tree[node*2+1].lbj+=tree[node].lbj;
	tree[node].mx+=tree[node].lbj;
	tree[node].mn+=tree[node].lbj;
	tree[node].lbj=0;
	add(L,R,v,node*2);
	add(L,R,v,node*2+1);
	tree[node].mn=min(tree[node*2].mn+tree[node*2].lbj,tree[node*2+1].mn+tree[node*2+1].lbj);
	tree[node].mx=max(tree[node*2].mx+tree[node*2].lbj,tree[node*2+1].mx+tree[node*2+1].lbj);
}
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	make_tree(1,N,1);
	char str[2];
	for(int q=1,x,y,z;q<=Q;q++)
	{
		mn=0x7FFFFFFF;mx=mn+1;
		scanf("%s",str);
		if(str[0]=='Q')
		{
			scanf("%d%d",&x,&y);
			solve(1,x,y);
			printf("%d\n",mx-mn);
		}
		else
		{
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z,1);
		}
	}
	return 0;
}
