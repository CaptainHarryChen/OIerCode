#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
#define MAXN 100005
int n,num[MAXN];
int son[MAXN*32][2],id[MAXN*32],tot=1;
struct Edge
{
	int val,id;
	Edge *next;
}E[MAXN*2],*cur=E,*head[MAXN];
void add_edge(int a,int b,int val)
{
	cur->val=val;
	cur->id=b;
	cur->next=head[a];
	head[a]=cur;
	cur++;
}
void dfs(int id=0,int sum=0,int last=-1)
{
	num[id]=sum;
	for(Edge *p=head[id];p;p=p->next)
		if(p->id!=last)
			dfs(p->id,sum^p->val,id);
}
int main()
{
	while(~scanf("%d",&n))
	{
		memset(num,0,sizeof num);
		memset(son,0,sizeof son);
		memset(id,0,sizeof id);tot=1;
		memset(E,0,sizeof E);cur=E;
		memset(head,0,sizeof head);
		int a,b,v;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&v);
			add_edge(a,b,v);
			add_edge(b,a,v);
		}
		dfs();
		int t,mx=0;
		int i,dig=30,now,c;
		for(i=1;i<=n;i++)
			mx=max(mx,num[i]);
		for(i=1;i<=n;i++)
		{
			now=0;
			t=(1<<dig);
			while(t)
			{
				c=!!(t&num[i]);
				if(!son[now][c])
					son[now][c]=tot++;
				now=son[now][c];
				t>>=1;
			}
			id[now]=i;
		}
		int ans=-1;
		for(int i=1;i<=n;i++)
		{
			t=(1<<dig);
			now=0;
			while(t)
			{
				c=!!(t&num[i]);
				if(son[now][!c])now=son[now][!c];
				else now=son[now][c];
				t>>=1;
			}
			ans=max(ans,(num[i]^num[id[now]]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
