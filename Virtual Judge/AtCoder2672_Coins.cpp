#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

struct Node
{int a,b,c;};

int X,Y,Z,N;
Node P[MAXN];

bool cmpab(const Node &x,const Node &y)
{return x.a-x.b>y.a-y.b;}
struct cmpbc
{
	bool operator () (const Node &x,const Node &y)const
	{return x.b-x.c>y.b-y.c;}
}BC;
struct cmpac
{
	bool operator () (const Node &x,const Node &y)const
	{return x.a-x.c>y.a-y.c;}
}AC;

priority_queue<Node,vector<Node>,cmpac> Q1;
priority_queue<Node,vector<Node>,cmpbc> Q2;
long long l[MAXN],r[MAXN];

int main()
{
	scanf("%d%d%d",&X,&Y,&Z);
	N=X+Y+Z;
	for(int i=1;i<=N;i++)
		scanf("%d%d%d",&P[i].a,&P[i].b,&P[i].c);
	sort(P+1,P+N+1,cmpab);
	long long sum=0;
	for(int i=1;i<=X;i++)
	{
		sum+=P[i].a;
		Q1.push(P[i]);
	}
	l[X]=sum;
	for(int i=X+1;i<=X+Z;i++)
	{
		if(Q1.empty()||AC(Q1.top(),P[i]))
			sum+=P[i].c;
		else
		{
			sum+=-Q1.top().a+Q1.top().c+P[i].a;
			Q1.pop();
			Q1.push(P[i]);
		}
		l[i]=sum;
	}
	sum=0;
	for(int i=N;i>N-Y;i--)
	{
		sum+=P[i].b;
		Q2.push(P[i]);
	}
	r[N-Y+1]=sum;
	for(int i=N-Y;i>X;i--)
	{
		if(Q2.empty()||BC(Q2.top(),P[i]))
			sum+=P[i].c;
		else
		{
			sum+=-Q2.top().b+Q2.top().c+P[i].b;
			Q2.pop();
			Q2.push(P[i]);
		}
		r[i]=sum;
	}
	long long ans=0;
	for(int i=0;i<=N;i++)
		ans=max(ans,l[i]+r[i+1]);
	printf("%lld\n",ans);
	
	return 0;
}
