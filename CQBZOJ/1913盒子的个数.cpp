#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 100000
struct TREE
{
	int l,r,box;
}tree[MAXN*2*4+5];
int L,R,N;
bool f[MAXN*2+5];
void build(int id,int L,int R)
{
	tree[id].l=L;tree[id].r=R;tree[id].box=0;
	if(L==R)return;
	int mid=(L+R)/2;
	build(id*2,L,mid);
	build(id*2+1,mid+1,R);
}
void insert(int id,int L,int R,int B)
{
	if(tree[id].r<L||tree[id].l>R)return;
	if(L<=tree[id].l&&tree[id].r<=R)
	{
		tree[id].box=B;
		return;
	}
	if(tree[id].box!=-1)
	{
		tree[id*2].box=tree[id*2+1].box=tree[id].box;
		tree[id].box=-1;
	}
	insert(id*2,L,R,B);
	insert(id*2+1,L,R,B);
}
int Count(int id)
{
	int cnt=0;
	if(tree[id].box!=-1)
	{
		if(f[tree[id].box])return 0;
		f[tree[id].box]=1;
		if(tree[id].box==0)
			return 0;
		else 
			return 1;
	}
	cnt+=Count(id*2);
	cnt+=Count(id*2+1);
	return cnt;
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
	printf("%d\n",Count(1));
	return 0;
}
