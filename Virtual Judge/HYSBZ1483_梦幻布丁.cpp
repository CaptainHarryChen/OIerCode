#include<cstdio>
#include<vector>
#define MAXN 100005
using namespace std;
int col[MAXN],loc[MAXN*10];
vector<int>S[MAXN*10];
int main()
{
	int op,a,b,ans,n,m;
	scanf("%d%d",&n,&m);
	ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",col+i);
		ans+=(col[i]!=col[i-1]);
		S[col[i]].push_back(i);
	}
	for(int i=1;i<MAXN*10;i++)
		loc[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==2)
			printf("%d\n",ans);
		else
		{
			scanf("%d%d",&a,&b);
			int x=loc[a],y=loc[b],s;
			if(x==y)continue;
			loc[a]=0;
			if(S[x].size()>S[y].size())
			{
				loc[b]=x;
				swap(x,y);
			}
			s=S[x].size();
			for(int j=0,id;j<s;j++)
			{
				id=S[x][j];
				if(id>1)ans-=(col[id-1]==y);
				if(id<n)ans-=(col[id+1]==y);
			}
			for(int j=0,id;j<s;j++)
			{
				id=S[x][j];
				col[id]=y;
				S[y].push_back(id);
			}
			S[x].clear();
		}
	}
	return 0;
}