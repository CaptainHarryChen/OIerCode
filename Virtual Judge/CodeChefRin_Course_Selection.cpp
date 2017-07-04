#include<cstdio>
#include<cstring>
#define MAXN 105
#define MAXV MAXN*MAXN
#define MAXE ((MAXN*MAXN)<<2)
#define min(a,b) (a>b?b:a)
#define INF 0x7FFFFFFF
struct Edge
{
	int id,w,next,back;
}E[MAXE];
int head[MAXV],_new=1;
void add_edge(int a,int b,int w)
{
	E[_new].id=b;E[_new].w=w;
	E[_new].next=head[a];
	head[a]=_new;_new++;
	E[_new].id=a;E[_new].w=0;
	E[_new].next=head[b];
	head[b]=_new;_new++;
	E[_new-2].back=_new-1;
	E[_new-1].back=_new-2;
}
int d[MAXV],cntd[MAXV];
int aug(int now,int augco,int S,int T,int n)
{
	int augc=augco,min_d=n-1,delta;
	if(now==T)return augc;
	for(int p=head[now];p;p=E[p].next)
		if(E[p].w>0)
		{
			if(d[E[p].id]==d[now]-1)
			{
				delta=min(augc,E[p].w);
				delta=aug(E[p].id,delta,S,T,n);
				E[p].w-=delta;
				E[E[p].back].w+=delta;
				augc-=delta;
				if(d[S]>=n)return augco-augc;
				if(augc==0)break;
			}
			min_d=min(min_d,d[E[p].id]);
		}
	if(augc==augco)
	{
		cntd[d[now]]--;
		if(cntd[d[now]]==0)
			d[S]=n;
		d[now]=min_d+1;
		cntd[d[now]]++;
	}
	return augco-augc;
}
int sap(int S,int T,int n)
{
	cntd[0]=n;
	int flow=0;
	while(d[S]<n)
		flow+=aug(S,INF,S,T,n);
	return flow;
}
int main()
{
	int N,M,K,S,T;
	scanf("%d%d%d",&N,&M,&K);
	S=N*M+1;T=N*M+2;
	for(int i=1,x,id;i<=N;i++)
		for(int j=1;j<=M;j++)
		{
			scanf("%d",&x);
			if(x==-1)x=INF;
			else x=100-x;
			id=(i-1)*M+j;
			if(j==1)
				add_edge(S,id,x);
			else
				add_edge(id-1,id,x);
			if(j==M)
				add_edge(id,T,INF);
		}
	for(int i=1,a,b;i<=K;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(S,(b-1)*M+1,INF);
		for(int j=2;j<=M;j++)
			add_edge((a-1)*M+j-1,(b-1)*M+j,INF);
	}
	int ans=sap(S,T,N*M+2);
	ans=100*N-ans;
	printf("%.2lf\n",1.0*ans/N);
	return 0;
}
