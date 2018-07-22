#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=MAXN*MAXN;

struct Edge
{
	int u,v;
	double a,b;
	Edge(){}
	Edge(int _u,int _v,double _a,double _b):u(_u),v(_v),a(_a),b(_b){}
};

int dsu[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return dsu[x]=Root(dsu[x]);
}

double k;
bool cmp(const Edge &x,const Edge &y)
{
	return x.a-k*x.b<y.a-k*y.b;
}

int N;
int hei[MAXN];
pair<int,int> pos[MAXN];
Edge edge[MAXM];

double dis(const pair<int,int> &a,const pair<int,int> &b)
{return sqrt(1.0*(a.first-b.first)*(a.first-b.first)+1.0*(a.second-b.second)*(a.second-b.second));}

int main()
{
	for(;;)
	{
		scanf("%d",&N);
		if(N==0)
			break;
		for(int i=1;i<=N;i++)
			scanf("%d%d%d",&pos[i].first,&pos[i].second,&hei[i]);
		int m=0;
		for(int i=1;i<=N;i++)
			for(int j=i+1;j<=N;j++)
				edge[++m]=Edge(i,j,abs(hei[i]-hei[j]),dis(pos[i],pos[j]));
		double ans=0,s1=0,s2=0;
		for(int i=1;i<N;i++)
		{
			s1+=edge[i].a;
			s2+=edge[i].b;
		}
		ans=s1/s2;
		for(;;)
		{
			::k=ans;
			sort(edge+1,edge+m+1,cmp);
			memset(dsu,0,sizeof dsu);
			s1=0,s2=0;
			for(int i=1;i<=m;i++)
			{
				int r1=Root(edge[i].u),r2=Root(edge[i].v);
				if(r1==r2)
					continue;
				dsu[r1]=r2;
				s1+=edge[i].a;
				s2+=edge[i].b;
			}
			if(s1/s2>=ans)
				break;
			ans=s1/s2;
		}
		printf("%.3lf\n",ans);
	}
	return 0;
}
