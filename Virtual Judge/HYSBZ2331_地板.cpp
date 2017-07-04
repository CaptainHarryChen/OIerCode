#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 105
#define HASHSIZE 180000
#define MOD 20110520
bool mp[MAXN][MAXN];
struct Hash
{
	int adj[HASHSIZE],sz;
	int state[HASHSIZE],val[HASHSIZE];
	int nex[HASHSIZE];
	void clear()
	{
		memset(adj,-1,sizeof adj);
		sz=0;
	}
	void insert(int st,int v)
	{
		int id=st%HASHSIZE;
		for(int i=adj[id];~i;i=nex[i])
			if(state[i]==st)
			{
				val[i]=(val[i]+v)%MOD;
				return;
			}
		state[sz]=st;
		val[sz]=v;
		nex[sz]=adj[id];
		adj[id]=sz;
		sz++;
	}
}dp[2];
void decode(int st,int c,int *res)
{
	memset(res,0,sizeof(int)*(c+3));
	for(int i=c+1;i>0;i--)
		res[i]=st&3,st>>=2;
}
int encode(int c,int *st)
{
	int res=0;
	for(int i=1;i<=c+1;i++)
		res=(res<<2)|st[i];
	return res;
}
int main()
{
	int r,c;
	scanf("%d%d",&r,&c);
	char inp[105];
	if(c>r)
	{
		for(int i=1;i<=r;i++)
		{
			scanf("%s",inp+1);
			for(int j=1;j<=c;j++)
				if(inp[j]=='*')
					mp[j][i]=1;
		}
		swap(r,c);
	}
	else
		for(int i=1;i<=r;i++)
		{
			scanf("%s",inp+1);
			for(int j=1;j<=c;j++)
				if(inp[j]=='*')
					mp[i][j]=1;
		}
	for(int i=0;i<=r+1;i++)
		mp[i][0]=mp[i][c+1]=1;
	for(int j=0;j<=c+1;j++)
		mp[0][j]=mp[r+1][j]=1;
	int temp[15];
	bool cur=0;
	dp[cur].clear();
	dp[cur].insert(0,1);
	cur=1;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++,cur^=1)
		{
			dp[cur].clear();
			for(int sid=0;sid<dp[cur^1].sz;sid++)
			{
				decode(dp[cur^1].state[sid],c,temp+(j==1));
				int &L=temp[j],&U=temp[j+1];
				if(mp[i][j])
				{
					if(!L&&!U)
					{
						L=U=0;
						dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
					}
				}
				else
				{
					if(L&&U)
					{
						if(L==1&&U==1)
						{
							L=U=0;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
					else if(L==1)
					{
						if(!mp[i][j+1])
						{
							L=0;U=1;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
						if(!mp[i+1][j])
						{
							L=3;U=0;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
					else if(L==3)
					{
						L=U=0;
						dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						if(!mp[i][j+1])
						{
							L=0;U=3;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
					else if(U==1)
					{
						if(!mp[i+1][j])
						{
							L=1;U=0;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
						if(!mp[i][j+1])
						{
							L=0;U=3;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
					else if(U==3)
					{
						L=U=0;
						dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						if(!mp[i+1][j])
						{
							L=3;U=0;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
					else
					{
						if(!mp[i+1][j])
						{
							L=1;U=0;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
						if(!mp[i][j+1])
						{
							L=0;U=1;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
						if(!mp[i][j+1]&&!mp[i+1][j])
						{
							L=3;U=3;
							dp[cur].insert(encode(c,temp),dp[cur^1].val[sid]);
						}
					}
				}
			}
		}
	int ans=0;
	bool flag;
	cur^=1;
	for(int i=0;i<dp[cur].sz;i++)
	{
		flag=1;
		decode(dp[cur].state[i],c,temp);
		for(int j=1;j<=c+1;j++)
			if(temp[j]==1){flag=0;break;}
		if(flag)
			ans=(ans+dp[cur].val[i])%MOD;
	}
	printf("%d\n",ans);
	return 0;
}
