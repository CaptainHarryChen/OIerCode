#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=73,MAXNODE=20000,MAXEDGE=730000;
struct Edge
{
	int to,w;
	Edge *next,*back;
}edges[MAXEDGE],*G[MAXNODE],*cur=edges;
void add_edge(int a,int b,int v)
{
	*cur=(Edge){b,v};
	cur->next=G[a];
	cur->back=cur+1;
	G[a]=cur;
	cur++;
	*cur=(Edge){a,0};
	cur->next=G[b];
	cur->back=cur-1;
	G[b]=cur;
	cur++;
}
namespace ISAP
{
	int cntd[MAXNODE],d[MAXNODE];
	int aug(int now,int augco,int S,int T,int n)
	{
		int augc=augco,mn=n-1,temp;
		if(now==T)return augco;
		for(Edge *p=G[now];p;p=p->next)
		{
			if(p->w<=0)continue;
			int u=p->to;
			if(d[u]==d[now]-1)
			{
				temp=std::min(augc,p->w);
				temp=aug(u,temp,S,T,n);
				p->w-=temp;
				p->back->w+=temp;
				augc-=temp;
				if(d[S]>=n)return augco-augc;
				if(augc==0)break;
			}
			mn=std::min(mn,d[u]);
		}
		if(augc==augco)
		{
			cntd[d[now]]--;
			if(cntd[d[now]]<=0)
				d[S]=n;
			d[now]=mn+1;
			cntd[d[now]]++;
		}
		return augco-augc;
	}
	int sap(int S,int T,int n)
	{
		memset(d,0,sizeof d);
		memset(cntd,0,sizeof cntd);
		cntd[0]=n;
		int flow=0;
		while(d[S]<n)
			flow+=aug(S,0x7FFFFFFF,S,T,n);
		return flow;
	}
}
int P,D,H,N,LTb,LTe;
int L[MAXN],R[MAXN][MAXN],F[MAXN][MAXN][MAXN];
int meeting[MAXN][MAXN];
void Read()
{
	memset(L,0,sizeof L);
	memset(R,0,sizeof R);
	memset(F,0,sizeof F);
	scanf("%d%d%d%d",&P,&D,&H,&N);
	for(int i=1;i<=P;i++)
		scanf("%d",L+i);
	scanf("%d%d",&LTb,&LTe);
	for(int i=1;i<=D;i++)
		for(int j=1;j<=H;j++)
			scanf("%d",&R[i][j]);
	memset(meeting,0,sizeof meeting);
	for(int i=1;i<=P;i++)
		for(int j=1;j<=D;j++)
			for(int k=1;k<=H;k++)
			{
				scanf("%d",&F[i][j][k]);
				meeting[i][j]+=(F[i][j][k]==0);
			}
}
int S,T;
bool MakeNet()
{
	S=-1;T=-1;
	for(int i=1;i<=P;i++)
		for(int j=1,cnt;j<=D;j++)
		{
			cnt=0;
			for(int k=LTb;k<=LTe;k++)
				cnt+=(F[i][j][k]==0);
			if(cnt>(LTe-LTb))return 0;
		}
	memset(G,0,sizeof G);
	memset(edges,0,sizeof edges);
	cur=edges;
	int p_id,pd_id;
	S=1;
	int id=D*H+1;
	for(int p=1;p<=P;p++)
	{
		id++;
		add_edge(S,id,L[p]);
		p_id=id;
		for(int d=1;d<=D;d++)
		{
			id++;
			if(N-meeting[p][d]<0)return 0;
			add_edge(p_id,id,N-meeting[p][d]);
			pd_id=id;
			{
				id++;
				add_edge(pd_id,id,LTe-LTb);
				for(int h=LTb;h<=LTe;h++)
					if(F[p][d][h])
						add_edge(id,(d-1)*H+h+1,1);
			}
			{
				id++;
				add_edge(pd_id,id,H-(LTe-LTb+1));
				for(int h=(1==LTb?LTe+1:1);h<=H;h=(h==LTb-1?LTe+1:h+1))
					if(F[p][d][h])
						add_edge(id,(d-1)*H+h+1,1);
			}
		}
	}
	T=++id;
	for(int d=1;d<=D;d++)
		for(int h=1;h<=H;h++)
			add_edge((d-1)*H+h+1,T,R[d][h]);
	return 1;
}
bool check()
{
	for(Edge *p=G[T];p;p=p->next)
		if(p->w<R[(p->to-1-1)/H+1][(p->to-1-1)%H+1])
			return 0;
	return 1;
}
int main()
{
	int test=1;
	scanf("%d",&test);
	while(test--)
	{
		Read();
		if(!MakeNet())
		{printf("No\n");continue;}
		ISAP::sap(S,T,T);
		if(check())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
