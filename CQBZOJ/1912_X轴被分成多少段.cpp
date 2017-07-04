#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100000
int XC,N;
struct Tree
{
	int l,r,col;
}tree[MAXN*2*4];
void build(int id,int L,int R)
{
	tree[id].l=L;tree[id].r=R;tree[id].col=XC;
	if(L==R)return;
	int mid=(L+R)/2;
	build(id*2,L,mid);
	build(id*2+1,mid+1,R);
}
void insert(int id,int L,int R,int C)
{
	if(tree[id].l>R||tree[id].r<L)return;
	if(tree[id].l>=L&&tree[id].r<=R)
	{
		tree[id].col=C;
		return;
	}
	if(tree[id].col!=-1)
	{
		tree[id*2].col=tree[id*2+1].col=tree[id].col;
		tree[id].col=-1;
	}
	insert(id*2,L,R,C);
	insert(id*2+1,L,R,C);
}
int Count(int id,int &lco,int &rco)
{
	int cnt=0,ll,lr,rl,rr;
	if(tree[id].col!=-1)
	{
		rco=lco=tree[id].col;
		return 1;
	}
	cnt+=Count(id*2,ll,lr);
	lco=ll;
	cnt+=Count(id*2+1,rl,rr);
	rco=rr;
	if(lr==rl)
		cnt--;
	return cnt;
}
int main()
{
	scanf("%d%d",&XC,&N);
	build(1,0,MAXN*2);
	for(int i=1,l,r,c;i<=N;i++)
	{
		scanf("%d%d%d",&l,&r,&c);
		l+=MAXN;r+=MAXN;
		insert(1,l,r-1,c);
	}
	int x,y;
	printf("%d\n",Count(1,x,y));
	return 0;
}
