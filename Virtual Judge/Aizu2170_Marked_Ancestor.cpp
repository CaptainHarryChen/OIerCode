#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
#define MAXN 100005
int Set[MAXN];
int Root(int x)
{return Set[x]==x?x:Set[x]=Root(Set[x]);}
int N,Q;
int fa[MAXN];
int Que[MAXN][2];
int marked[MAXN];
int main()
{
	char op[3];
	int id;
	long long ans;
	while(~scanf("%d%d",&N,&Q)&&N&&Q)
	{
		memset(Que,0,sizeof Que);
		memset(fa,0,sizeof fa);
		memset(Set,0,sizeof Set);
		memset(marked,0,sizeof marked);
		ans=0;
		Set[1]=1;fa[1]=1;
		for(int i=2;i<=N;i++)
		{
			scanf("%d",fa+i);
			Set[i]=fa[i];
		}
		for(int i=1;i<=Q;i++)
		{
			scanf("%s%d",op,&id);
			if(op[0]=='Q')Que[i][0]=1;
			else {Que[i][0]=2;Set[id]=id;marked[id]++;}
			Que[i][1]=id;
		}
		for(int i=Q;i>=1;i--)
		{
			if(Que[i][0]==1)
				ans+=1LL*Root(Que[i][1]);
			else
			{
				marked[Que[i][1]]--;
				if(!marked[Que[i][1]])
					Set[Que[i][1]]=fa[Que[i][1]];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
