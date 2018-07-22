#include<cstdio>
#include<cstring>
const int MAXN=10005,MAXM=30005,MAXK=100005;

int N,M;

bool vis[MAXN+MAXM];
int dsu[MAXN+MAXM];
int Root(int u)
{
	if(dsu[u]==0)
		return u;
	return dsu[u]=Root(dsu[u]);
}
void Union(int u,int v)
{
	int r1=Root(u),r2=Root(v);
	if(r1!=r2)
		dsu[r1]=r2;
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		int k,l;
		scanf("%d",&k);
		while(k--)
		{
			scanf("%d",&l);
			Union(i,l+N);
		}
	}
	
	int cnt=0;
	for(int i=1;i<=N;i++)
		if(!vis[Root(i)])
		{
			cnt++;
			vis[Root(i)]=true;
		}
	printf("%d\n",cnt-1);
	
	return 0;
}
