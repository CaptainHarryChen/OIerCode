#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXM=200005;
struct Edge
{
	int u,v,id;
	int c,w;
	bool operator < (const Edge &t)const
	{return w<t.w;}
};
bool number(const Edge &a,const Edge &b)
{return a.id<b.id;}
struct Edge_list
{
	int v,c,w,id;
	Edge_list *next;
	Edge_list(){}
	Edge_list(int _v,int _c,int _w,int _id)
	{next=NULL,v=_v,c=_c,w=_w,id=_id;}
};
class LCAtree
{
private:
	int fa[MAXN][20],val[MAXN][20],id[MAXN][20],mlog;
	int lev[MAXN];
	Edge_list E[MAXM*2],*cur;
	void dfs(int u,int f,int level)
	{
		for(Edge_list *p=V[u];p;p=p->next)
			if(p->v!=f)
			{
				lev[p->v]=level+1;
				fa[p->v][0]=u;
				val[p->v][0]=p->w;
				id[p->v][0]=p->id;
				dfs(p->v,u,level+1);
			}
	}
public:
	Edge_list *V[MAXN];
	LCAtree()
	{cur=E;}
	void add_edge(const Edge &t)
	{
		*cur=Edge_list(t.v,t.c,t.w,t.id);
		cur->next=V[t.u];
		V[t.u]=cur++;
		*cur=Edge_list(t.u,t.c,t.w,t.id);
		cur->next=V[t.v];
		V[t.v]=cur++;
	}
	void Init(int n)
	{
		dfs(1,0,0);
		for(int j=1;(1<<j)<=n;j++)
		{
			mlog=j;
			for(int i=1;i<=n;i++)
				if(lev[i]>=(1<<j))
				{
					fa[i][j]=fa[fa[i][j-1]][j-1];
					if(val[i][j-1]>=val[fa[i][j-1]][j-1])
						id[i][j]=id[i][j-1];
					else
						id[i][j]=id[fa[i][j-1]][j-1];
					val[i][j]=max(val[i][j-1],val[fa[i][j-1]][j-1]);
				}
		}
	}
	int LCA(int a,int b,int &mx,int &iid)
	{
		mx=0;iid=0;
		if(lev[a]<lev[b])
			swap(a,b);
		for(int i=mlog;i>=0;i--)
			if(lev[a]-(1<<i)>=lev[b])
			{
				if(val[a][i]>mx)
				{
					mx=val[a][i];
					iid=id[a][i];
				}
				a=fa[a][i];
			}
		if(a==b)
			return a;
		for(int i=mlog;i>=0;i--)
			if(lev[a]-(1<<i)>=0&&fa[a][i]!=fa[b][i])
			{
				if(val[a][i]>mx)
				{
					mx=val[a][i];
					iid=id[a][i];
				}
				if(val[b][i]>mx)
				{
					mx=val[b][i];
					iid=id[b][i];
				}
				a=fa[a][i];
				b=fa[b][i];
			}
		if(val[a][0]>mx)
		{
			mx=val[a][0];
			iid=id[a][0];
		}
		if(val[b][0]>mx)
		{
			mx=val[b][0];
			iid=id[b][0];
		}
		return fa[a][0];
	}
};
class UFset
{
private:
	int fa[MAXN];
public:
	int Find(int x)
	{
		if(fa[x]==0)
			return x;
		return fa[x]=Find(fa[x]);
	}
	void Union(int x,int y)
	{
		int r1=Find(x),r2=Find(y);
		if(r1==r2)return;
		fa[r1]=r2;
	}
};
Edge E[MAXM];
bool used[MAXM];
LCAtree L;
UFset U;
int main()
{
	int n,m,S;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&E[i].w);
	for(int i=1;i<=m;i++)
		scanf("%d",&E[i].c);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&E[i].u,&E[i].v);
		E[i].id=i;
	}
	scanf("%d",&S);
	sort(E+1,E+m+1);
	int r1,r2;
	long long W=0,ans;
	for(int i=1;i<=m;i++)
	{
		r1=U.Find(E[i].u);
		r2=U.Find(E[i].v);
		if(r1!=r2)
		{
			U.Union(r1,r2);
			L.add_edge(E[i]);
			used[E[i].id]=true;
			W+=1LL*E[i].w;
		}
	}
	L.Init(n);
	sort(E+1,E+m+1,number);
	ans=W;
	int a=0,b=0,c=0,mxw,idw;
	for(int i=1;i<=m;i++)
	{
		if(used[E[i].id])
		{
			if(ans>W-S/E[i].c)
			{
				ans=W-S/E[i].c;
				a=b=E[i].id;
				c=E[i].w-S/E[i].c;
			}
		}
		else
		{
			L.LCA(E[i].u,E[i].v,mxw,idw);
			if(ans>W-mxw+E[i].w-S/E[i].c)
			{
				ans=W-mxw+E[i].w-S/E[i].c;
				a=idw;b=E[i].id;c=E[i].w-S/E[i].c;
			}
		}
	}
	printf("%I64d\n",ans);
	for(int i=1;i<=m;i++)
		if(used[i])
		{
			if(i==a)
				printf("%d %d\n",b,c);
			else
				printf("%d %d\n",i,E[i].w);
		}
	return 0;
}
