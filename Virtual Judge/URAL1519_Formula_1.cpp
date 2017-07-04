#include<cstdio>
#include<cstring>
#define MAXN 15
#define MAX_STATE 1000005
#define HASH_SIZE 240000
int n,m;
bool Map[MAXN][MAXN];
void decode(long long st,int t[])
{
	for(int i=m;i>=0;i--)
		t[i]=st&7,st>>=3;
}
long long encode(int t[])
{
	int num[MAXN]={0};
	long long ret=0;
	int k=0;
	for(int i=0;i<=m;i++)
	{
		if(!num[t[i]]&&t[i])
			num[t[i]]=++k;
		ret=(ret<<3)|num[t[i]];
	}
	return ret;
}
struct Hash
{
	int size;
	int adj[HASH_SIZE];
	int next[MAX_STATE];
	long long state[MAX_STATE],val[MAX_STATE];
	Hash(){clear();}
	void clear()
	{
		size=0;
		memset(adj,-1,sizeof adj);
	}
	void insert(long long st,long long v)
	{
		int id=st%HASH_SIZE;
		for(int i=adj[id];~i;i=next[i])
			if(state[i]==st)
			{
				val[i]+=v;
				return;
			}
		state[size]=st;
		val[size]=v;
		next[size]=adj[id];
		adj[id]=size;
		size++;
	}
}dp[2];bool cur;
int endx,endy;
int temp[MAXN];
void Merge(int x,int y,int t[])
{
	for(int i=0;i<=m;i++)
		if(t[i]==x)
			t[i]=y;
}
void DpBlank(int x,int y)
{
	for(int k=0;k<dp[cur^1].size;k++)
	{
		decode(dp[cur^1].state[k],temp);
		int &L=temp[y-1],&U=temp[y];
		if(L&&U)
		{
			if(L==U)
			{
				if(x==endx&&y==endy)
				{
					L=U=0;
					dp[cur].insert(encode(temp)>>(3*(y==m)),dp[cur^1].val[k]);
				}
			}
			else
			{
				Merge(L,U,temp);
				L=U=0;
				dp[cur].insert(encode(temp)>>(3*(y==m)),dp[cur^1].val[k]);
			}
		}
		else if(L)
		{
			if(Map[x+1][y])
				dp[cur].insert(dp[cur^1].state[k]>>(3*(y==m)),dp[cur^1].val[k]);
			if(Map[x][y+1])
			{	
				U=L;L=0;
				dp[cur].insert(encode(temp)>>(3*(y==m)),dp[cur^1].val[k]);
			}
		}
		else if(U)
		{
			if(Map[x+1][y])
			{
				L=U;U=0;
				dp[cur].insert(encode(temp)>>(3*(y==m)),dp[cur^1].val[k]);
			}
			if(Map[x][y+1])
				dp[cur].insert(dp[cur^1].state[k]>>(3*(y==m)),dp[cur^1].val[k]);
		}
		else
		{
			if(Map[x][y+1]&&Map[x+1][y])
			{
				L=U=m+1;
				dp[cur].insert(encode(temp)>>(3*(y==m)),dp[cur^1].val[k]);
			}
		}
	}
}
void DpBlock(int x,int y)
{
	for(int k=0;k<dp[cur^1].size;k++)
		dp[cur].insert(dp[cur^1].state[k]>>(3*(y==m)),dp[cur^1].val[k]);
}
void DP()
{
	cur=0;
	dp[cur].clear();
	dp[cur].insert(0,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cur^=1;
			dp[cur].clear();
			if(Map[i][j])
				DpBlank(i,j);
			else
				DpBlock(i,j);
		}
}
int main()
{
	char ch;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf(" %c",&ch);
			if(ch=='.')
				Map[endx=i][endy=j]=1;
			else
				Map[i][j]=0;
		}
	DP();
	long long ans=0;
	for(int i=0;i<dp[cur^1].size;i++)
		ans+=dp[cur^1].val[i];
	printf("%I64d\n",ans);
	return 0;
}
