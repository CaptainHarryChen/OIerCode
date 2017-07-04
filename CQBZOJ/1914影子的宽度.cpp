#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 100000
struct TREE
{
	int l,r,cnt;
}tree[MAXN*2*4+5];
int L,R,N;
bool f[MAXN*2+5];
void build(int id,int L,int R)
{
	tree[id].l=L;tree[id].r=R;tree[id].cnt=0;
	if(L==R)return;
	int mid=(L+R)/2;
	build(id*2,L,mid);
	build(id*2+1,mid+1,R);
}
int insert(int id,int L,int R,int B)
{
	if(tree[id].r<L||tree[id].l>R)return tree[id].cnt;
	if(L<=tree[id].l&&tree[id].r<=R)
	{
		tree[id].cnt=tree[id].r-tree[id].l+1;
		return tree[id].cnt;
	}
	if(tree[id].cnt==tree[id].r-tree[id].l+1)
	{
		tree[id*2].cnt=tree[id*2].r-tree[id*2].l+1;
		tree[id*2+1].cnt=tree[id*2+1].r-tree[id*2+1].l+1;
		return tree[id].cnt;
	}
	tree[id].cnt=insert(id*2,L,R,B);
	tree[id].cnt+=insert(id*2+1,L,R,B);
	return tree[id].cnt;
}
int main()
{
	scanf("%d%d%d",&L,&R,&N);
	int X=-L;
	R+=X;
	L=0;
	build(1,L,R);
	for(int i=1,bl,br;i<=N;i++)
	{
		scanf("%d%d",&bl,&br);
		bl+=X;br+=X;
		insert(1,bl,br-1,i);
	}
	printf("%d\n",tree[1].cnt);
	return 0;
}
