#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXL=20;

namespace LCA
{
	int fa[MAXN][MAXL+3],lev[MAXN];
	vector<int>V[MAXN];
	void dfs(int u,int pa,int level)
	{
		fa[u][0]=pa;
		lev[u]=level;
		for(int i=0;i<(int)V[u].size();i++)
			if(V[u][i]!=pa)
				dfs(V[u][i],u,level+1);
	}
	void Init(int n)
	{
		memset(fa,0,sizeof fa);
		memset(lev,0,sizeof lev);
		dfs(1,0,1);
		for(int j=1;(1<<j)<=n;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int findLCA(int a,int b)
	{
		if(lev[a]>lev[b])
			swap(a,b);
		for(int i=MAXL;i>=0;i--)
			if(lev[b]-(1<<i)>=lev[a])
				b=fa[b][i];
		if(a==b)
			return a;
		for(int i=MAXL;i>=0;i--)
			if(lev[a]-(1<<i)>=1&&fa[a][i]!=fa[b][i])
				a=fa[a][i],b=fa[b][i];
		return fa[a][0];
	}
}

namespace Trie
{
	struct Node
	{
		int cnt;
		Node *son[2];
	};
	Node nodes[MAXN*MAXL],*rt[MAXN],*cur,*null;
	void Init()
	{
		memset(nodes,0,sizeof nodes);
		memset(rt,0,sizeof rt);
		null=nodes;
		null->cnt=0;
		null->son[0]=null->son[1]=null;
		cur=nodes+1;
		rt[0]=null;
	}
	void Insert(Node *&u,int a,int k)
	{
		*cur=*u;
		u=cur;
		cur++;
		u->cnt++;
		if(k<0)return;
		Insert(u->son[(a>>k)&1],a,k-1);
	}
	int Query(Node *a,Node *b,Node *l,Node *lf,int num,int k)
	{
		if(k<0)return 0;
		int ch[2];
		ch[0]=(a->son[0]->cnt)+(b->son[0]->cnt)-(l->son[0]->cnt)-(lf->son[0]->cnt);
		ch[1]=(a->son[1]->cnt)+(b->son[1]->cnt)-(l->son[1]->cnt)-(lf->son[1]->cnt);
		int d=(num>>k)&1;
		if(ch[d^1])
			return (1<<k)+Query(a->son[d^1],b->son[d^1],l->son[d^1],lf->son[d^1],num,k-1);
		return Query(a->son[d],b->son[d],l->son[d],lf->son[d],num,k-1);
	}
}

int A[MAXN];

void make_trie(int len,int u,int pa)
{
	using namespace LCA;
	using namespace Trie;
	rt[u]=rt[pa];
	Insert(rt[u],A[u],len);
	for(int i=0;i<(int)V[u].size();i++)
		if(V[u][i]!=pa)
			make_trie(len,V[u][i],u);
}
int solve(int x,int y,int z,int len)
{
	int l=LCA::findLCA(x,y);
	int lf=LCA::fa[l][0];
	using namespace Trie;
	return Query(rt[x],rt[y],rt[l],rt[lf],z,len);
}

int main()
{
	int n,m,len,a,b,x,y,z;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		len=17;
		for(int i=1;i<=n;i++)
			scanf("%d",A+i);
		for(int i=1;i<=n;i++)
			LCA::V[i].clear();
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			LCA::V[a].push_back(b);
			LCA::V[b].push_back(a);
		}
		LCA::Init(n);
		Trie::Init();
		make_trie(len,1,0);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			printf("%d\n",solve(x,y,z,len));
		}
	}
	return 0;
}
