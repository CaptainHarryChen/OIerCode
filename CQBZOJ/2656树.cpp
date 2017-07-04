#include<cstring>
#include<sstream>
#include<iostream>
#define MAXN 10010
using namespace std;
struct node
{
	int v,l,r;
}tree[MAXN];
int cnt,s1[MAXN],s2[MAXN],n,root,ans,minsum;
string input;
void make_tree(int *u,int l,int r,int t)
{
	int x;
	for(x=l;s1[x]!=s2[t]&&x<=r;x++);
	if(x==r+1)return;
	*u=cnt++;
	tree[*u].v=s2[t];
	make_tree(&tree[*u].l,l,x-1,t-r+x-1);
	make_tree(&tree[*u].r,x+1,r,t-1);
}
void dfs(int u,int sum)
{
	if(u==0)return;
	if(!tree[u].l&&!tree[u].r)
	{
		if(sum<minsum)
		{
			minsum=sum;
			ans=tree[u].v;
		}
		else if(sum==minsum)
			if(tree[u].v<ans)
				ans=tree[u].v;
		return;
	}
	dfs(tree[u].l,sum+tree[tree[u].l].v);
	dfs(tree[u].r,sum+tree[tree[u].r].v);
}
int main()
{
	while(getline(cin,input,'\n'))
	{
		minsum=(1<<31)-1;
		cnt=1;
		memset(tree,0,sizeof tree);
		stringstream i1(input);
		for(n=1;i1>>s1[n];n++);
		getline(cin,input,'\n');
		stringstream i2(input);
		for(n=1;i2>>s2[n];n++);
		make_tree(&root,1,n-1,n-1);
		dfs(root,tree[root].v);
		cout<<ans<<endl;
	}
	return 0;
}
