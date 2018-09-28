#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long N,M;
vector<long long> adj[MAXN];
long long dep[MAXN],sum[MAXN],k[MAXN];
bool vis[MAXN];
long long cU,cV,clen;
vector<long long> num;

void dfs(long long u,long long fa=0)
{
	vis[u]=true;
	for(auto v:adj[u])
	{
		if(v==fa)
			continue;
		if(vis[v])
		{
			cU=u;
			cV=v;
			clen=dep[u]-dep[v]+1;
			continue;
		}
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
void Calc(long long u,long long fa=0)
{
	vis[u]=true;
	for(auto v:adj[u])
	{
		if(v==fa||vis[v])
			continue;
		Calc(v,u);
		sum[u]+=sum[v];
		k[u]+=k[v];
	}
}

int main()
{
	scanf("%lld%lld",&N,&M);
	for(long long i=1;i<=M;i++)
	{
		long long a,b;
		scanf("%lld%lld",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dep[1]=0;
	dfs(1);
	long long val=0;
	long long ans=0;
	for(long long i=1;i<=N;i++)
	{
		sum[i]=(dep[i]&1)?1:-1;
		val+=sum[i];
	}
	if(M==N-1)
	{
		if(val!=0)
		{
			puts("-1");
			return 0;
		}
	}
	else
	{
		if(clen&1)
		{
			if(val&1)
			{
				puts("-1");
				return 0;
			}
			else
			{
				ans+=(abs(val)/2);
				sum[cU]-=val/2;
				sum[cV]-=val/2;
			}
		}
		else
		{
			if(val!=0)
			{
				puts("-1");
				return 0;
			}
			else
			{
				k[cU]=1;
				k[cV]=-1;
			}
		}
	}
	memset(vis,0,sizeof vis);
	Calc(1);
	for(long long i=1;i<=N;i++)
	{
		if(k[i]==0)
			ans+=abs(sum[i]);
		else
		{
			if(k[i]==1)
				sum[i]=-sum[i];
			num.push_back(sum[i]);
		}
	}
	num.push_back(0);
	sort(num.begin(),num.end());
	long long x=num[(num.size()-1)/2];
	for(auto s:num)
		ans+=1LL*abs(s-x);
	printf("%lld\n",ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}