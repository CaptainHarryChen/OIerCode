#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2147483647
#define MAXN 100100
using namespace std;
int a[MAXN],b[MAXN],c[MAXN],n,k,Queue[MAXN];
struct node
{
	int l,r,sc;
}tree[MAXN*4];
void sort_(int x,int y)
{
	int mid=a[(x+y)/2];
	int i=x,j=y;
	while(j>=i)
	{
		while(a[i]<mid)i++;
		while(a[j]>mid)j--;
		if(j>=i)
		{
			swap(a[i],a[j]);
			swap(b[i],b[j]);
			i++;
			j--;
		}
	}
	if(x<j)sort_(x,j); 
	if(y>i)sort_(i,y);
}
bool check()
{
	sort_(1,n);
	for(int i=n,j=n;i>=1;i--)
	{
		for(;a[j]>a[i];j--);
		c[i]=n-j;
		if(c[i]<b[i])
			return 0;
	}
	return 1;
}
void build_tree(int i,int l,int r)
{
	tree[i].l=l;tree[i].r=r;tree[i].sc=r-l+1;
	if(r==l)return;
	int mid=(l+r)/2;
	build_tree(i*2,l,mid);
	build_tree(i*2+1,mid+1,r);
}
int quety_tree(int i,int l,int r)
{
	if(l==r)return l;
	int mid=(l+r)/2;
	if(k<=tree[i*2].sc)
		return quety_tree(i*2,l,mid);
	else
	{
		k-=tree[i*2].sc;
		return quety_tree(i*2+1,mid+1,r);
	}
}
void modify_tree(int i,int l,int r)
{
	tree[i].sc--;
	if(l==r)return;
	int mid=(l+r)/2;
	if(k<=mid)
		modify_tree(i*2,l,mid);
	else
		modify_tree(i*2+1,mid+1,r);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	if(!check())
	{printf("impossible\n");return 0;}
	build_tree(1,1,n);
	for(int i=1;i<=n;i++)
	{
		k=min(b[i]+1,c[i]-b[i]+1);
		k=quety_tree(1,1,n);
		Queue[k]=a[i];
		modify_tree(1,1,n);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",Queue[i]);
	printf("\n");
	return 0;
}
