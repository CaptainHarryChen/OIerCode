#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=15,MAXA=500005,INF=0x3F3F3F3F;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;

vector<int> adj[MAXA],len[MAXA];
long long dis[MAXA];
bool inq[MAXA];
queue<int> Q;

void SPFA(int s)
{
	memset(dis,0x3F,sizeof dis);
	dis[s]=0;
	Q.push(s);
	inq[s]=true;
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(dis[v]>dis[u]+len[u][i])
			{
				dis[v]=dis[u]+len[u][i];
				if(!inq[v])
				{
					Q.push(v);
					inq[v]=true;
				}
			}
		}
	}
}

int N;
long long Bmin,Bmax;
int a[MAXN];

int main()
{
	scanf("%d%lld%lld",&N,&Bmin,&Bmax);
	int T=INF;
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	sort(a+1,a+N+1);
	int st;
	for(int i=1;i<=N;i++)
		if(a[i]!=0)
		{st=i;T=a[i];break;}
	if(T==INF)
	{
		puts("0");
		return 0;
	}
	for(int i=0;i<T;i++)
		for(int j=st;j<=N;j++)
		{
			adj[i].push_back((i+a[j])%T);
			len[i].push_back(a[j]);
		}
		
	SPFA(0);
	
	long long ans=0;
	for(int i=0;i<T;i++)
		if(dis[i]<=Bmax)
		{
			long long L=max(0LL,(Bmin-dis[i])/T);
			if(L*T+dis[i]<Bmin)
				L++;
			long long R=max(0LL,(Bmax-dis[i])/T);
			if(R*T+dis[i]>Bmax)
				R--;
			ans+=(R-L+1);
		}
	printf("%lld\n",ans);
	
	return 0;
}
