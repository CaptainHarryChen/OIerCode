#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;
const int MAXN=205;
 
int N;
vector<int> adj[MAXN];
bool vis[MAXN];
int match[MAXN];
 
bool aug(int u)
{
	for(int i=0;i<(int)adj[u].size();i++)
		if(!vis[adj[u][i]])
		{
			int v=adj[u][i];
			vis[v]=true;
			if(match[v]==0||aug(match[v]))
			{
				match[u]=v;
				match[v]=u;
				return true;
			}
		}
	return false;
}
 
int Match()
{
	int ans=0;
	for(int i=1;i<=2*N;i++)
		if(match[i]==0)
		{
			memset(vis,0,sizeof vis);
			ans+=aug(i);
		}
	return ans;
}
 
pair<int,int> A[MAXN],B[MAXN];
 
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&A[i].first,&A[i].second);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&B[i].first,&B[i].second);
		
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if(A[i].first<B[j].first&&A[i].second<B[j].second)
			{
				adj[i].push_back(j+N);
				adj[j+N].push_back(i);
			}
	
	printf("%d\n",Match());
	
	return 0;
}
