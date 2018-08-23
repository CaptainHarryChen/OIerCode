#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=3005;

long long ans=0x7F7F7F7F7F7F7F7FLL;
long long n,m,cnt;
vector<pair<long long,long long> > p[MAXN];
vector<pair<long long,long long> > v;
long long id[MAXN],par[MAXN];

void solve(long long lim)
{
	long long sum=0;
	long long cnt=::cnt;
	for(long long i=1;i<=m;i++)
		if((long long)p[i].size()>=lim)
		{
			sum+=p[i][p[i].size()-lim].first;
			cnt+=p[i].size()-lim+1;
		}
	for(long long i=0;i<(long long)v.size()&&cnt<lim;i++)
	{
		long long a=id[v[i].second],pa=par[v[i].second];
		if(a>(long long)p[pa].size()-lim)
		{
			sum+=v[i].first;
			cnt++;
		}
	}
	ans=min(ans,sum);
}

int main()
{
	scanf("%I64d%I64d",&n,&m);
	for(long long i=1;i<=n;i++)
	{
		long long a,b;
		scanf("%I64d%I64d",&a,&b);
		if(a!=1)
		{
			p[a].push_back(make_pair(b,i));
			v.push_back(make_pair(b,i));
		}
		else
			cnt++;
	}
	for(long long i=2;i<=m;i++)
	{
		sort(p[i].begin(),p[i].end());
		for(long long j=0;j<(long long)p[i].size();j++)
		{
			id[p[i][j].second]=j;
			par[p[i][j].second]=i;
		}
		for(long long j=1;j<(long long)p[i].size();j++)
			p[i][j].first+=p[i][j-1].first;
	}
	sort(v.begin(),v.end());
	for(long long i=max(cnt,1LL);i<=n;i++)
		solve(i);
	printf("%I64d\n",ans);
	
	return 0;
}