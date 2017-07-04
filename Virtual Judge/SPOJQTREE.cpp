#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 20005
struct Edge
{
	int x,v,id;
	int next;
	Edge():x(0),v(0),id(0),next(0){}
	Edge(int x,int v,int id):x(x),v(v),id(id),next(0){}
}E[MAXN*2];
int E_V[MAXN];
int ecnt;
int V[MAXN];
void add_edge(int a,int b,int w,int id)
{
	ecnt++;
	E[ecnt]=Edge(b,w,id);
	E[ecnt].next=V[a];
	V[a]=ecnt;
}
int father[MAXN];
bool perfer[MAXN];
int value[MAXN];
int mx[MAXN];
int son[MAXN][2];
bool vis[MAXN];
void Build(int id=1)
{
	vis[id]=1;
	for(int i=V[id];i;i=E[i].next)
		if(!vis[E[i].x])
		{
			father[E[i].x]=id;
			value[E[i].x]=E[i].v;
			mx[E[i].x]=E[i].v;
			E_V[E[i].id]=E[i].x;
			Build(E[i].x);
		}
}
void Update(int x)
{
	mx[x]=value[x];
	if(son[x][0])mx[x]=max(mx[x],mx[son[x][0]]);
	if(son[x][1])mx[x]=max(mx[x],mx[son[x][1]]);
}
void Rotate(int x,int d)
{
	int y=father[x];
	father[x]=father[y];
	perfer[x]=perfer[y];
	if(father[y]&&perfer[y])
		son[father[y]][son[father[y]][1]==y]=x;
	perfer[y]=1;
	son[y][!d]=son[x][d];
	if(son[x][d])
		father[son[x][d]]=y;
	son[x][d]=y;
	father[y]=x;
	Update(y);
}
void Splay(int x)
{
	int y,z;
	while(perfer[x])
	{
		y=father[x];
		if(!perfer[y])
		{
			Rotate(x,son[y][0]==x);
			break;
		}
		z=father[y];
		if((son[z][0]==y)==(son[y][0]==x))
		{
			Rotate(y,son[z][0]==y);
			Rotate(x,son[y][0]==x);
		}
		else
		{
			Rotate(x,son[y][0]==x);
			Rotate(x,son[z][0]==x);
		}
	}
	Update(x);
}
void Access(int x)
{
	int last=0;
	while(x)
	{
		Splay(x);
		perfer[son[x][1]]=0;
		son[x][1]=last;
		if(last)perfer[last]=1;
		Update(x);
		last=x;
		x=father[last];
	}
}
void Change(int x,int y)
{
	x=E_V[x];
	value[x]=y;
	Access(x);
}
int Query(int x,int y)
{
	Access(x);
	int last=0,ans=0;
	while(y)
	{
		Splay(y);
		if(!father[y])
			ans=max(mx[last],mx[son[y][1]]);
		perfer[son[y][1]]=0;
		son[y][1]=last;
		if(last)perfer[last]=1;
		Update(y);
		last=y;
		y=father[last];
	}
	return ans;
}
int main()
{
	int test;
	scanf("%d",&test);
	char op[10];
	int x,y;
	while(test--)
	{
		int n;
		scanf("%d",&n);
		ecnt=0;
		memset(E,0,sizeof E);
		memset(E_V,0,sizeof E_V);
		memset(V,0,sizeof V);
		memset(vis,0,sizeof vis);
		memset(father,0,sizeof father);
		memset(perfer,0,sizeof perfer);
		memset(value,0,sizeof value);
		memset(son,0,sizeof son);
		for(int i=1,a,b,w;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&w);
			add_edge(a,b,w,i);
			add_edge(b,a,w,i);
		}
		Build();
		while(1)
		{
			scanf("%s",op);
			if(op[0]=='D')break;
			scanf("%d%d",&x,&y);
			if(op[0]=='Q')
				printf("%d\n",Query(x,y));
			else
				Change(x,y);
		}
	}
	return 0;
}