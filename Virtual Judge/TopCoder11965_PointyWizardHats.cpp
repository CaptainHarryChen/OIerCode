#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;

class PointyWizardHats
{
	static const int MAXN=200;
	
	int n,m;
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
		for(int i=1;i<=n+m;i++)
			if(match[i]==0)
			{
				memset(vis,0,sizeof vis);
				ans+=aug(i);
			}
		return ans;
	}
	
public:
	int getNumHats(vector<int> &h1,vector<int> &r1,vector<int> &h2,vector<int> &r2)
	{
		n=h1.size();
		m=h2.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(r1[i]<r2[j]&&h1[i]-1.0*h2[j]*(1.0*r1[i]/r2[j])>1e-6)
				{
					adj[i+1].push_back(n+j+1);
					adj[n+j+1].push_back(i+1);
				}
		return Match();
	}
};

int n,m;
PointyWizardHats solve;
vector<int> h1,r1,h2,r2;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		h1.push_back(x);
	}
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		r1.push_back(x);
	}
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		h2.push_back(x);
	}
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		r2.push_back(x);
	}
	printf("%d\n",solve.getNumHats(h1,r1,h2,r2));
	
	return 0;
}
