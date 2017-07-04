#include<cstdio>
#include<iostream>
using namespace std;
int s;
struct dian
{
	int v;
	dian *next;
}a[205];
bool f[205];
void dfs(int k)
{
	f[k]=1;
	s++;
	for(dian*p=&a[k];p!=NULL;p=p->next)
		if(f[p->v]==0)
			dfs(p->v);
}
int main()
{
	int n,m,k;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		a[i].v=i;
		a[i].next=NULL;
	}
	int x,y;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		dian *p=new dian;
		p->v=y-1;
		p->next=a[x-1].next;
		a[x-1].next=p;
	}
	cin>>k;
	dfs(k-1);
	cout<<s<<endl;
	return 0;
}
