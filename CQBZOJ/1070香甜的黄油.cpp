#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=505,MAXP=805;
struct State
{
	int d,id;
	State(){}
	State(int _d,int _id)
	{d=_d;id=_id;}
	bool operator < (const State &t)const
	{return d>t.d;}
};
struct Edge
{
	int v,val;
	Edge(){}
	Edge(int _v,int _val)
	{v=_v;val=_val;}
};
vector<Edge>G[MAXP];
int cow[MAXN];
int dis[MAXP];
int N,P,C;
priority_queue<State> Q;
int main()
{
    int A,B,D;
    scanf("%d%d%d",&N,&P,&C);
    for(int i=1;i<=N;i++)
        scanf("%d",cow+i);
    for(int i=1;i<=C;i++)
    {
        scanf("%d%d%d",&A,&B,&D);
        G[A].push_back(Edge(B,D));
        G[B].push_back(Edge(A,D));
    }
    int sum,ans=0x7FFFFFFF;
    for(int i=1;i<=P;i++)
    {
		int s=i;
		fill(dis+1,dis+P+1,0x7FFFFFFF);
		dis[s]=0;
		Q.push(State(0,s));
		State t;
		while(!Q.empty())
		{
			t=Q.top();
			Q.pop();
			if(t.d>dis[t.id])
				continue;
			for(int i=0;i<int(G[t.id].size());i++)
			{
				int v=G[t.id][i].v,w=G[t.id][i].val;
				if(dis[v]>dis[t.id]+w)
				{
					dis[v]=dis[t.id]+w;
					Q.push(State(dis[v],v));
				}
			}
		}
        sum=0;
        for(int j=1;j<=N;j++)
            sum+=dis[cow[j]];
        ans=min(ans,sum);
    }
    printf("%d\n",ans);
	return 0;
}
