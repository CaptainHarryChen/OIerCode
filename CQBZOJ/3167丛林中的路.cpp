#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 1000
int n,i,side_cnt,set[30];
struct side
{
	int v,a,b;
	side(){a=b=v=0;}
}arr[MAXN];
bool used[MAXN];
bool cmp(side a,side b){return a.v<b.v;}
void input()
{
	side_cnt=0;
	for(int i=1,m;i<n;i++)
	{
		char s[2],t[2];
		scanf("%s%d",s,&m);
		for(int j=1,x;j<=m;j++)
		{
			scanf("%s%d",t,&x);
			arr[++side_cnt].a=s[0]-'A'+1;
			arr[side_cnt].b=t[0]-'A'+1;
			arr[side_cnt].v=x;
		}
	}
	std::sort(arr+1,arr+side_cnt+1,cmp);
}
int root(int u)
{
	if(set[u]==u)return u;
	return set[u]=root(set[u]);
}
int make_min_tree()
{
	memset(used,0,sizeof used);
	for(int i=1;i<=n;i++)
		set[i]=i;
	int ans=0;
	for(int i=1,r1,r2,j=0;i<=side_cnt&&j<n;i++)
	{
		r1=root(arr[i].a);r2=root(arr[i].b);
		if(r1!=r2)
		{
			set[r1]=r2;
			ans+=arr[i].v;
			j++;
		}
	}
	return ans;
}
int main()
{
	while(1)
	{
		scanf("%d",&n);
		if(!n)break;
		input();
		int ans=make_min_tree();
		printf("%d\n",ans);
	}
	return 0;
}
