#include<cstdio>
#include<set>
const long long MAXN=100005;
struct Edge
{
	long long to,len;
	Edge *nxt;
	Edge(){}
	Edge(long long _t,long long _l){to=_t;len=_l;nxt=NULL;}	
};
Edge edges[MAXN<<1],*E[MAXN],*cur=edges;
void AddEdge(long long u,long long v,long long l)
{
	*cur=Edge(v,l);
	cur->nxt=E[u];
	E[u]=cur;
	cur++;
}
long long mn[MAXN*2][20],dis[MAXN*2];
long long dfn[MAXN],dfnn,log_2[MAXN*2];
void DFS_init(long long now,long long fa=0)
{
	dfn[now]=++dfnn;
	mn[dfnn][0]=dis[now];
	for(Edge *p=E[now];p;p=p->nxt)
		if(p->to!=fa)
		{
			dis[p->to]=dis[now]+p->len;
			DFS_init(p->to,now);
			mn[++dfnn][0]=dis[now];
		}
}
void RMQ_Init()
{
	for(long long i=2;i<=dfnn;i++)
		log_2[i]=log_2[i>>1]+1;
	for(long long j=1;j<=log_2[dfnn];j++)
		for(long long i=1;i+(1<<j)-1<=dfnn;i++)
			mn[i][j]=std::min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
}
long long RMQ(long long l,long long r)
{
	long long lg=log_2[r-l+1];
	return std::min(mn[l][lg],mn[r-(1<<lg)+1][lg]);
}
bool statu[MAXN];
long long ans;
std::set<long long>S;
long long LCA_Dis()
{
	if(S.size()==0)return 0;
	std::set<long long>::iterator st,ed;
	st=S.begin();
	ed=S.end();ed--;
	return RMQ(*st,*ed);
}
void Insert(long long x)
{
	std::set<long long>::iterator it,nex,pre;
	it=S.insert(x).first;
	ans+=mn[x][0];
	if(it==S.begin())pre=S.end();
	else pre=(--it)++;
	if((++it)==S.end())nex=S.end(),it--;
	else nex=it--;
	if(nex!=S.end())
		ans-=RMQ(*it,*nex);
	if(pre!=S.end())
		ans-=RMQ(*pre,*it);
	if(nex!=S.end()&&pre!=S.end())
		ans+=RMQ(*pre,*nex);
}
void Delete(long long x)
{
	std::set<long long>::iterator it,nex,pre;
	it=S.find(x);
	ans-=mn[x][0];
	if(it==S.begin())pre=S.end();
	else pre=(--it)++;
	if((++it)==S.end())nex=S.end(),it--;
	else nex=it--;
	if(nex!=S.end())
		ans+=RMQ(*it,*nex);
	if(pre!=S.end())
		ans+=RMQ(*pre,*it);
	if(nex!=S.end()&&pre!=S.end())
		ans-=RMQ(*pre,*nex);
	S.erase(it);
}
int main()
{
	long long n,m,u,v,l;
    scanf("%lld%lld",&n,&m);
	for(long long i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&u,&v,&l);
		AddEdge(u,v,l);
		AddEdge(v,u,l);
	}
	DFS_init(1);
	RMQ_Init();
	for(long long i=1,x;i<=m;i++)
	{
		scanf("%lld",&x);
		if(statu[x])
		{statu[x]=0;Delete(dfn[x]);}
		else
		{statu[x]=1;Insert(dfn[x]);}
		printf("%lld\n",(ans-LCA_Dis())<<1);
	}
	return 0;
}
