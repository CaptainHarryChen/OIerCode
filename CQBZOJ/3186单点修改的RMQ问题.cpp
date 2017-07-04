#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 50005
struct NODE
{
	int l,r,mn,mx;
}tree[MAXN*4];
int _new=1,N,Q,A[MAXN];
void make_tree(int L,int R,int node)
{
	tree[node].l=L,tree[node].r=R;
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
		mx=max(mx,tree[node].mx);
		mn=min(mn,tree[node].mn);
		return;
	}
	solve(node*2,l,r);
	solve(node*2+1,l,r);
}
void add(int id,int v,int node)
{
	if(tree[node].l>id||tree[node].r<id)
		return;
	if(tree[node].l==id&&tree[node].r==id)
	{
		tree[node].mx=tree[node].mn=A[id];
		return;
	}
	add(id,v,node*2);
	add(id,v,node*2+1);
	tree[node].mn=min(tree[node*2].mn,tree[node*2+1].mn);
	tree[node].mx=max(tree[node*2].mx,tree[node*2+1].mx);
}
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	make_tree(1,N,1);
	char str[2];
	for(int q=1,x,y;q<=Q;q++)
	{
		mn=0x7FFFFFFF;mx=mn+1;
		scanf("%s%d%d",str,&x,&y);
		if(str[0]=='Q')
		{
			solve(1,x,y);
			printf("%d\n",mx-mn);
		}
		else
		{
			A[x]+=y;
			add(x,y,1);
		}
	}
	return 0;
}
