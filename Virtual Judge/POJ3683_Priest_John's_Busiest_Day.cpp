#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=10300,MAXM=MAXN*MAXN*4;
bool overlap(int a,int b,int c,int d)
{
	return (c<b&&a<d);
}
vector<int>G[MAXN*2],rG[MAXN*2],g[MAXN*2];
int other[MAXN*2];
bool vis[MAXN*2];
int st[MAXN*2],top;
int blkid[MAXN*2],blkc;
int col[MAXN];
void dfs(int u)
{
	vis[u]=true;
	for(int i=0;i<G[u].size();i++)
		if(!vis[G[u][i]])
			dfs(G[u][i]);
	st[++top]=u;
}
bool rdfs(int u)
{
	blkid[u]=blkc;
	if(blkid[u^1]==blkc)
		return false;
	for(int i=0;i<rG[u].size();i++)
		if(!blkid[rG[u][i]])
			if(!rdfs(rG[u][i]))
				return false;
	return true;
}
bool check(int N)
{
	memset(vis,0,sizeof vis);
	top=0;
	for(int i=0;i<N;i++)
		if(!vis[i])
			dfs(i);
	memset(blkid,0,sizeof blkid);
	blkc=0;
	while(top)
	{
		if(!blkid[st[top]])
		{
			blkc++;
			if(!rdfs(st[top]))
				return false;
		}
		top--;
	}
	return true;
}
int T[MAXN][2];
int cer[MAXN];
int main()
{
	int N,a,b;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d:%d",&a,&b);
		T[i][0]=a*60+b;
		scanf("%d:%d",&a,&b);
		T[i][1]=a*60+b;
		scanf("%d",cer+i);
	}
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			if(i==j)
				continue;
			if(overlap(T[i][0],T[i][0]+cer[i],T[j][0],T[j][0]+cer[j]))
			{
				G[i*2].push_back(j*2+1);
				rG[j*2+1].push_back(i*2);
			}
			if(overlap(T[i][0],T[i][0]+cer[i],T[j][1]-cer[j],T[j][1]))
			{
				G[i*2].push_back(j*2);
				rG[j*2].push_back(i*2);
			}
			if(overlap(T[i][1]-cer[i],T[i][1],T[j][0],T[j][0]+cer[j]))
			{
				G[i*2+1].push_back(j*2+1);
				rG[j*2+1].push_back(i*2+1);
			}
			if(overlap(T[i][1]-cer[i],T[i][1],T[j][1]-cer[j],T[j][1]))
			{
				G[i*2+1].push_back(j*2);
				rG[j*2].push_back(i*2+1);
			}
		}
	if(!check(N*2))
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=0;i<N*2;i++)
	{
		other[blkid[i]]=blkid[i^1];
		for(int j=0;j<(int)G[i].size();j++)
			if(blkid[i]!=blkid[G[i][j]])
				g[blkid[i]].push_back(blkid[G[i][j]]);
	}
	for(int i=blkc;i>0;i--)
		if(!col[i])
		{
			col[i]=1;
			col[other[i]]=2;
		}
	for(int i=0;i<N;i++)
	{
		if(col[blkid[i*2]]==1)
			printf("%02d:%02d %02d:%02d\n",T[i][0]/60,T[i][0]%60,(T[i][0]+cer[i])/60,(T[i][0]+cer[i])%60);
		else
			printf("%02d:%02d %02d:%02d\n",(T[i][1]-cer[i])/60,(T[i][1]-cer[i])%60,T[i][1]/60,T[i][1]%60);
	}
	return 0;
}
