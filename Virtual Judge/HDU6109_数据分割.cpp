#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
const int MAXL=100005;
set<int>ineq[MAXL];
struct UFset
{
	int fa[MAXL];
	void clear()
	{
		memset(fa,-1,sizeof fa);
	}
	int Root(int x)
	{
		if(fa[x]==-1)
			return x;
		for(set<int>::iterator it=ineq[x].begin();it!=ineq[x].end();it++)
			ineq[fa[x]].insert(*it);
		return fa[x]==-1?x:(fa[x]=Root(fa[x]));
	}
	void Union(int x,int y)
	{
		int r1=Root(x),r2=Root(y);
		if(r1==r2)return;
		fa[r1]=r2;
	}
};
UFset eq;
int ans[MAXL];
int main()
{
	int L,datacnt,setcnt,x,y,e;
	bool flag;
	while(scanf("%d",&L)!=EOF)
	{
		eq.clear();
		for(int i=1;i<=L;i++)
			ineq[i].clear();
		datacnt=1;
		setcnt=0;
		flag=0;
		for(int i=1;i<=L;i++)
		{
			scanf("%d%d%d",&x,&y,&e);
			x=eq.Root(x);y=eq.Root(y);
			if(e==1)
			{
				if(ineq[x].find(y)!=ineq[x].end())
					flag=1;
				else
					eq.Union(x,y);
			}
			if(e==0)
			{
				if(x==y)
					flag=1;
				else
				{
					ineq[x].insert(y);
					ineq[y].insert(x);
				}
			}
			if(flag)
			{
				ans[datacnt]=setcnt+1;
				eq.clear();
				for(int i=1;i<=L;i++)
					ineq[i].clear();
				setcnt=-1;
				datacnt++;
				flag=0;
			}
			setcnt++;
		}
		datacnt--;
		printf("%d\n",datacnt);
		for(int i=1;i<=datacnt;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
