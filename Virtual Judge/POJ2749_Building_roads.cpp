#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int MAXN=505,MAXM=MAXN*MAXN*4;
typedef pair<int,int> coo;
int dis(coo a,coo b)
{
	return abs(a.first-b.first)+abs(a.second-b.second);
}
vector<int>G[MAXN*2],rG[MAXN*2];
coo S1,S2,barn[MAXN];
int other[MAXN*2];
bool vis[MAXN*2];
int st[MAXN*2],top;
int blkid[MAXN*2],blkc;
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
int like[MAXN][2],dlike[MAXN][2];
int main()
{
	int N,A,B,a,b,L=0,R=0,mid,S;
	scanf("%d%d%d",&N,&A,&B);
	scanf("%d%d%d%d",&S1.first,&S1.second,&S2.first,&S2.second);
	S=dis(S1,S2);
	for(int i=0;i<N;i++)
		scanf("%d%d",&barn[i].first,&barn[i].second);
	for(int i=1;i<=A;i++)
	{
		scanf("%d%d",dlike[i],dlike[i]+1);
		dlike[i][0]--;dlike[i][1]--;
	}
	for(int i=1;i<=B;i++)
	{
		scanf("%d%d",like[i],like[i]+1);
		like[i][0]--;like[i][1]--;
	}
	R=6000005;
	while(L<R)
	{
		mid=(L+R)/2;
		for(int i=0;i<2*N;i++)
		{
			G[i].clear();
			rG[i].clear();
		}
		for(int i=1;i<=A;i++)
		{
			a=dlike[i][0],b=dlike[i][1];
			G[a*2].push_back(b*2+1);
			G[a*2+1].push_back(b*2);
			G[b*2].push_back(a*2+1);
			G[b*2+1].push_back(a*2);
			rG[b*2+1].push_back(a*2);
			rG[b*2].push_back(a*2+1);
			rG[a*2+1].push_back(b*2);
			rG[a*2].push_back(b*2+1);
		}
		for(int i=1;i<=B;i++)
		{
			a=like[i][0],b=like[i][1];
			G[a*2].push_back(b*2);
			G[a*2+1].push_back(b*2+1);
			G[b*2].push_back(a*2);
			G[b*2+1].push_back(a*2+1);
			rG[b*2].push_back(a*2);
			rG[b*2+1].push_back(a*2+1);
			rG[a*2].push_back(b*2);
			rG[a*2+1].push_back(b*2+1);
		}
		for(int i=0;i<N;i++)
			for(int j=0;j<i;j++)
			{
				if(i==j)
					continue;
				if(dis(barn[i],S1)+dis(barn[j],S1)>mid)
				{
					G[i*2].push_back(j*2+1);
					G[j*2].push_back(i*2+1);
					rG[j*2+1].push_back(i*2);
					rG[i*2+1].push_back(j*2);
				}
				if(dis(barn[i],S1)+S+dis(barn[j],S2)>mid)
				{
					G[i*2].push_back(j*2);
					G[j*2+1].push_back(i*2+1);
					rG[j*2].push_back(i*2);
					rG[i*2+1].push_back(j*2+1);
				}
				if(dis(barn[i],S2)+S+dis(barn[j],S1)>mid)
				{
					G[i*2+1].push_back(j*2+1);
					G[j*2].push_back(i*2);
					rG[j*2+1].push_back(i*2+1);
					rG[i*2].push_back(j*2);
				}
				if(dis(barn[i],S2)+dis(barn[j],S2)>mid)
				{
					G[i*2+1].push_back(j*2);
					G[j*2+1].push_back(i*2);
					rG[j*2].push_back(i*2+1);
					rG[i*2].push_back(j*2+1);
				}
			}
		if(check(N*2))
			R=mid;
		else
			L=mid+1;
	}
	if(L==6000005)
		printf("-1\n");
	else
		printf("%d\n",L);
	return 0;
}
