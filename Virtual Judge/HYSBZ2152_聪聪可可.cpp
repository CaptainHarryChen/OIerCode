#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=20005;

int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}

struct Edge
{
	int v,val;
	Edge *nxt;
}E[MAXN*2],*V[MAXN],*cur=E;
void add_edge(int u,int v,int val)
{
	cur->v=v;cur->val=val;
	cur->nxt=V[u];
	V[u]=cur++;
}

bool mark[MAXN];
int siz[MAXN],val[MAXN];
int res,best;
void calc_g(int u,int pa=0)
{
	siz[u]=1;val[u]=0;
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&!mark[p->v])
		{
			calc_g(p->v,u);
			siz[u]+=siz[p->v];
			val[u]=max(val[u],siz[p->v]);
		}
}
void findbest(int n,int u,int pa=0)
{
	val[u]=max(val[u],n-siz[u]);
	if(best>val[u])
	{
		best=val[u];
		res=u;
	}
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&!mark[p->v])
			findbest(n,p->v,u);
}
int find_g(int u)
{
	calc_g(u);
	best=0x7FFFFFFF;
	findbest(siz[u],u);
	return res;
}
int S[3],temp[3];
int calc(int u,int pa,int val)
{
	int ret=0;
	temp[val]++;
	ret+=S[(3-val)%3];
	for(Edge *p=V[u];p;p=p->nxt)
		if(p->v!=pa&&!mark[p->v])
			ret+=calc(p->v,u,(val+p->val)%3);
	return ret;
}
queue<int>Q;
int solve(int n)
{
	int ret=0;
	Q.push(1);
	while(!Q.empty())
	{
		int u=Q.front();Q.pop();
		S[0]=1;S[1]=0;S[2]=0;
		int g=find_g(u);
		mark[g]=true;
		for(Edge *p=V[g];p;p=p->nxt)
			if(!mark[p->v])
			{
				temp[0]=temp[1]=temp[2]=0;
				ret+=calc(p->v,g,p->val%3);
				S[0]+=temp[0];S[1]+=temp[1];S[2]+=temp[2];
				Q.push(p->v);
			}
	}
	return ret;
}

int main()
{
	int n,a,b,c;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	int ans1=solve(n)*2+n;
	int ans2=n*n;
	int g=gcd(ans1,ans2);
	ans1/=g;ans2/=g;
	printf("%d/%d\n",ans1,ans2);
	return 0;
}
