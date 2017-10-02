#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=105;
const double EPS=1e-4;
typedef pair<double,int> State;
typedef pair<int,int> Coo;
struct Edge
{
	int v,val;
	Edge *next;
};
double Dis(Coo a,Coo b)
{return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));}
bool isRight(double a,double b,double c)
{return abs(a*a+b*b-c*c)<=EPS;}
double dis[MAXN*4];
Coo airp[MAXN*4];
priority_queue<State>Q;
int s,t,A,B,Ti[MAXN];
void Dijkstra()
{
	for(int i=0;i<s*4;i++)
		dis[i]=1e100;
	dis[A*4]=0;
	dis[A*4+1]=0;
	dis[A*4+2]=0;
	dis[A*4+3]=0;
	Q.push(State(0,A*4));
	Q.push(State(0,A*4+1));
	Q.push(State(0,A*4+2));
	Q.push(State(0,A*4+3));
	State temp;
	int a,b;
	double ndis;
	while(!Q.empty())
	{
		temp=Q.top();
		Q.pop();
		if(temp.first>dis[temp.second])
			continue;
		a=temp.second%4;
		b=temp.second/4;
		for(int i=0;i<4;i++)
		{
			if(i==a)continue;
			ndis=temp.first+Dis(airp[temp.second],airp[b*4+i])*Ti[b];
			if(dis[b*4+i]>ndis)
			{
				dis[b*4+i]=ndis;
				Q.push(State(ndis,b*4+i));
			}
		}
		for(int i=0;i<s*4;i++)
		{
			if(i/4==b)
				continue;
			ndis=temp.first+Dis(airp[temp.second],airp[i])*t;
			if(dis[i]>ndis)
			{
				dis[i]=ndis;
				Q.push(State(ndis,i));
			}
		}
	}
}
int main()
{
	int T,a,b,c;
	double ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&s,&t,&A,&B);
		A--;B--;
		for(int i=0;i<s;i++)
		{
			scanf("%d%d%d%d%d%d",&airp[i*4].first,&airp[i*4].second,&airp[i*4+1].first,&airp[i*4+1].second,&airp[i*4+2].first,&airp[i*4+2].second);
			scanf("%d",Ti+i);
			if(isRight(Dis(airp[i*4],airp[i*4+1])
						,Dis(airp[i*4+1],airp[i*4+2])
						,Dis(airp[i*4],airp[i*4+2])))
				a=i*4+1,b=i*4,c=i*4+2;
			if(isRight(Dis(airp[i*4],airp[i*4+2])
						,Dis(airp[i*4+1],airp[i*4+2])
						,Dis(airp[i*4],airp[i*4+1])))
				a=i*4+2,b=i*4,c=i*4+1;
			if(isRight(Dis(airp[i*4],airp[i*4+1])
						,Dis(airp[i*4],airp[i*4+2])
						,Dis(airp[i*4+1],airp[i*4+2])))
				a=i*4,b=i*4+1,c=i*4+2;
			airp[i*4+3]=Coo(airp[b].first+airp[c].first-airp[a].first,
							airp[b].second+airp[c].second-airp[a].second);
		}
		Dijkstra();
		ans=1e100;
		for(int i=0;i<4;i++)
			ans=min(ans,dis[B*4+i]);
		printf("%.2lf\n",ans);
	}
	return 0;
}
