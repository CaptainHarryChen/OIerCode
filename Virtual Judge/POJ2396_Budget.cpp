#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXE 50000
#define MAXV 4300
#define MAXN 205
#define MAXM 25
#define INF 0x7FFFFFFF
#define code(a,b) ((a-1)*M+b+N+M)
int n,S,T;
int d[MAXV],cntd[MAXV];
struct Edge
{
	int id,w;
	int next;
	Edge(){}
	Edge(int _id,int _w){id=_id;w=_w;next=0;}
}edge[MAXE];
int _new,head[MAXV];
int G[MAXN][MAXM][2];
void add_edge(int a,int b,int w)
{
	int p;
	for(p=head[a];p&&edge[p].id!=b;p=edge[p].next);
	if(p){edge[p].w+=w;}
	else
	{
		edge[_new]=Edge(b,w);
		edge[_new].next=head[a];
		head[a]=_new;
		_new++;
	}
	for(p=head[b];p&&edge[p].id!=a;p=edge[p].next);
	if(!p)
	{
		edge[_new]=Edge(a,0);
		edge[_new].next=head[b];
		head[b]=_new;
		_new++;
	}
}
int aug(int now,int augco)
{
	int augc=augco,mn=n-1;
	if(now==T)
		return augco;
	for(int p=head[now],temp;p;p=edge[p].next)
		if(edge[p].w>0)
		{
			if(d[edge[p].id]==d[now]-1)
			{
				temp=min(augc,edge[p].w);
				temp=aug(edge[p].id,temp);
				edge[p].w-=temp;
				int q;
				for(q=head[edge[p].id];q&&edge[q].id!=now;q=edge[q].next);
				edge[q].w+=temp;
				augc-=temp;
				if(d[S]>=n)return augco-augc;
				if(augc==0)break;
			}
			mn=min(mn,d[edge[p].id]);
		}
	if(augco==augc)
	{
		cntd[d[now]]--;
		if(cntd[d[now]]==0)
			d[S]=n;
		d[now]=mn+1;
		cntd[d[now]]++;
	}
	return augco-augc;
}
int sap()
{
	memset(cntd,0,sizeof cntd);
	memset(d,0,sizeof d);
	int flow=0;
	cntd[0]=n;
	while(d[S]<n)
		flow+=aug(S,INF);
	return flow;
}
bool check()
{
	for(int p=head[S];p;p=edge[p].next)
		if(edge[p].w>0)
			return 0;
	return 1;
}
int N,M;
int main()
{
	int test;
	scanf("%d",&test);
	while(test--)
	{
		_new=1;
		memset(head,0,sizeof head);
		memset(edge,0,sizeof edge);
		scanf("%d%d",&N,&M);
		int ss=N*M+N+M+1,tt=ss+1;
		S=tt+1,T=S+1;
		for(int i=1,x;i<=N;i++)
		{
			scanf("%d",&x);
			add_edge(ss,T,x);
			add_edge(S,i,x);
		}
		for(int i=1,x;i<=M;i++)
		{
			scanf("%d",&x);
			add_edge(i+N,T,x);
			add_edge(S,tt,x);
		}
		for(int i=1;i<=N;i++)
			for(int j=1;j<=M;j++)
			{
				G[i][j][0]=0;
				G[i][j][1]=INF;
			}
		int C,a,b,w;
		char op[3];
		scanf("%d",&C);
		bool flag=1;
		for(int i=1;i<=C;i++)
		{
			scanf("%d%d%s%d",&a,&b,op,&w);
			for(int aa=a==0?1:a;((a==0&&aa<=N)||(a&&aa==a))&&flag;aa++)
				for(int bb=b==0?1:b;((b==0&&bb<=M)||(b&&bb==b))&&flag;bb++)
				{
					if(op[0]=='>')
					{
						if(G[aa][bb][0]>w)continue;
						G[aa][bb][0]=w+1;
						if(G[aa][bb][0]>G[aa][bb][1])
						{flag=0;break;}
					}
					if(op[0]=='=')
					{
						if(G[aa][bb][0]>w||G[aa][bb][1]<w)
						{flag=0;break;}
						G[aa][bb][0]=G[aa][bb][1]=w;
					}
					if(op[0]=='<')
					{
						if(G[aa][bb][1]<w)continue;
						G[aa][bb][1]=w-1;
						if(G[aa][bb][1]<G[aa][bb][0])
						{flag=0;break;}
					}
				}
		}
		if(flag)
		{
			for(int i=1;i<=N;i++)
				for(int j=1;j<=M;j++)
				{
					add_edge(i,T,G[i][j][0]);
					add_edge(S,code(i,j),G[i][j][0]);
					add_edge(i,code(i,j),G[i][j][1]-G[i][j][0]);
					add_edge(code(i,j),T,G[i][j][0]);
					add_edge(S,j+N,G[i][j][0]);
					add_edge(code(i,j),j+N,G[i][j][1]-G[i][j][0]);
				}
			add_edge(tt,ss,INF);
			n=T;
			sap();
		}
		if(!flag||!check())
			printf("IMPOSSIBLE\n");
		else
			for(int i=1,p,q;i<=N;i++)
			{
				for(int j=1;j<M;j++)
				{
					for(p=head[(i-1)*M+j+N+M];p&&edge[p].id!=i;p=edge[p].next);
					for(q=head[(i-1)*M+j+N+M];q&&edge[q].id!=S;q=edge[q].next);
					printf("%d ",edge[p].w+edge[q].w);
				}
				for(p=head[(i-1)*M+M+N+M];p&&edge[p].id!=i;p=edge[p].next);
				for(q=head[(i-1)*M+M+N+M];q&&edge[q].id!=S;q=edge[q].next);
				printf("%d\n",edge[p].w+edge[q].w);
			}
		if(test>1)printf("\n");
	}
	return 0;
}
