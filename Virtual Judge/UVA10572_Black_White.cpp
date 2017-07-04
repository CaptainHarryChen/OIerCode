#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
#define MAXN 10
#define HASH_SIZE 233333
#define MAX_NODE 1000000
struct Hash
{
	int size,adj[HASH_SIZE],next[HASH_SIZE],col[HASH_SIZE];
	int state[HASH_SIZE],val[HASH_SIZE];
	void clear();
	void insert(int,int,int,int,int,char);
}dp[2];
bool cur;
int n,m,temp[MAXN],pre[MAXN*MAXN][HASH_SIZE];
char Map[MAXN][MAXN],op[MAXN*MAXN][HASH_SIZE];
void decode(int,int[]);
int encode(int[]);
void solve();
void doDp(int,int,int);
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		memset(Map,0,sizeof Map);
		for(int i=0;i<n;i++)
			scanf("%s",Map[i]);
		solve();
		puts("");
	}
	return 0;
}
void Hash::clear()
{
	size=0;
	memset(adj,-1,sizeof adj);
}
void Hash::insert(int st,int c,int v,int pos,int fa,char OP)
{
	int id=st%HASH_SIZE;
	for(int i=adj[id];~i;i=next[i])
		if(state[i]==st&&col[i]==c)
		{
			val[i]+=v;
			return;
		}
	state[size]=st;
	val[size]=v;
	col[size]=c;
	pre[pos][size]=fa;
	op[pos][size]=OP;
	next[size]=adj[id];
	adj[id]=size;
	size++;
}
void decode(int st,int t[])
{
	for(int i=m-1;i>=0;i--)
		t[i]=st&7,st>>=3;
}
int encode(int t[])
{
	int num[MAXN];
	memset(num,-1,sizeof num);
	int k=-1;
	int ret=0;
	for(int i=0;i<m;i++)
	{
		if(num[t[i]]==-1)
			num[t[i]]=++k;
		ret=(ret<<3)|num[t[i]];
	}
	return ret;
}
void solve()
{
	cur=0;
	dp[cur].clear();
	dp[cur].insert(0,0,1,0,0,0);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			dp[cur^1].clear();
			if(Map[i][j]!='#')doDp(i,j,0);
			if(Map[i][j]!='o')doDp(i,j,1);
			cur^=1;
		}
	int ans=0,k;
	for(int i=0;i<dp[cur].size;i++)
	{
		int mx=0;
		decode(dp[cur].state[i],temp);
		for(int j=0;j<m;j++)
			mx=max(mx,temp[j]);			
		if(mx>1)continue;
		ans+=dp[cur].val[i];
		k=i;		
	}
	printf("%d\n",ans);		
	if(ans)
	{
		for(int i=n-1;i>=0;i--)
			for(int j=m-1;j>=0;j--)
			{
				Map[i][j]=op[i*m+j][k];
				k=pre[i*m+j][k];				}
		for(int i=0;i<n;i++)
			puts(Map[i]);
	}
}
void doDp(int i,int j,int c)
{
	for(int k=0;k<dp[cur].size;k++)
	{
		int cc=dp[cur].col[k];
		int U=i?(cc>>j&1)==c:0;
		int L=j?(cc>>(j-1)&1)==c:0;
		int LU=(cc>>m)==c;
		if(U&&L&&LU)
			continue;
		if(i==n-1&&j==m-1&&!U&&!L&&LU)
			continue;
		decode(dp[cur].state[k],temp);
		if(i&&!U)
		{
			int s1=0,s2=0;
			for(int t=0;t<m;t++)
			{
				if(temp[t]==temp[j])
					s1++;
				if((cc>>t&1)!=c)s2++;
			}
			if(s1==1)
			{
				if(s2>1)continue;
				if(i<n-1||j<m-2)continue;
			}
		}
		if(U&&L)
		{
			if(temp[j]!=temp[j-1])
				for(int k=0;k<m;k++)
					if(temp[k]==temp[j])
						temp[k]=temp[j-1];
		}
		else if(!U&&L)
			temp[j]=temp[j-1];
		else if(!U&&!L)temp[j]=m;
		if(cc&(1<<j))
			cc|=1<<m;
		else
			cc&=~(1<<m);
		if(c)
			cc|=1<<j;
		else
			cc&=~(1<<j);
		dp[cur^1].insert(encode(temp),cc,dp[cur].val[k],i*m+j,k,c?'#':'o');
	}
}
