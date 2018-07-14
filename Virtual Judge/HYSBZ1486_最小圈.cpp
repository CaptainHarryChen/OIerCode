#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=3005;

int N,M;

double dis[MAXN];
bool inq[MAXN];
vector<int> adj[MAXN];
vector<double> len[MAXN];

void AddEdge(int u,int v,double l)
{
	adj[u].push_back(v);
	len[u].push_back(l);
}

bool check(int u,double ans)
{
	inq[u]=true;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(dis[v]>dis[u]+len[u][i]-ans)
		{
			dis[v]=dis[u]+len[u][i]-ans;
			if(inq[v])
				return true;
			else
			{
				if(check(v,ans))
					return true;
			}
		}
	}
	inq[u]=false;
	return false;
}

bool HasNCircle(double ans)
{
	memset(dis,0,sizeof dis);
	memset(inq,0,sizeof inq);
	for(int i=1;i<=N;i++)
		if(check(i,ans))
			return true;
	return false;
}

int main()
{
	int A,B;
	double D;
	scanf("%d%d",&N,&M);
	double L=1e100,R=-1e100;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%lf",&A,&B,&D);
		AddEdge(A,B,D);
		L=min(L,D);
		R=max(R,D);
	}
	
	while(R-L>1e-10)
	{
		double mid=(L+R)/2.0;
		if(HasNCircle(mid))
			R=mid;
		else
			L=mid;
	}
	printf("%.8lf\n",L);
	
	return 0;
}
