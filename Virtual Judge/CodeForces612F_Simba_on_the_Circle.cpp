#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005;

int n,m,s;
int getdis(int u,int v)
{
	if(u>v)
		swap(u,v);
	return min(v-u,n-(v-u));
}
int A[MAXN];
int num[MAXN];
vector<int> pos[MAXN];
int dis[MAXN],dis2[MAXN];
int path[MAXN],dir[MAXN],ed[MAXN];

void Move(int u,int v)
{
	int d=getdis(u,v);
	if(d==v-u||d==v+n-u)
		printf("%+d\n",d);
	else
		printf("%+d\n",-d);
}

int main()
{
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);
		num[i]=A[i];
	}
	sort(num+1,num+n+1);
	m=unique(num+1,num+n+1)-num-1;
	for(int i=1;i<=n;i++)
		A[i]=lower_bound(num+1,num+m+1,A[i])-num;
	for(int i=1;i<=n;i++)
		pos[A[i]].push_back(i);
	memset(dis,0x3F,sizeof dis);
	memset(dis2,0x3F,sizeof dis2);
	pos[0].push_back(s);
	for(int a=0;a<(int)pos[m].size();a++)
		dis[pos[m][a]]=0;
	for(int i=m;i>=0;i--)
	{
		if(i<m)
		{
			for(int a=0;a<(int)pos[i].size();a++)
			{
				int u=pos[i][a];
				if(i==0)
					u=0;
				for(int b=0;b<(int)pos[i+1].size();b++)
				{
					int v=pos[i+1][b],d=getdis(u==0?s:u,v);
					if(dis[u]>dis2[v]+d)
					{
						dis[u]=dis2[v]+d;
						path[u]=v;
					}
				}
			}
		}
		if(i==0)
			break;
		int siz=pos[i].size();
		for(int a=0;a<siz;a++)
		{
			int u=pos[i][a];
			int v=pos[i][(a+1)%siz];
			dir[u]=-1;ed[u]=v;
			if(u==v)
			{dis2[u]=dis[v];continue;}
			dis2[u]=dis[v]+(v>u?(n-(v-u)):(u-v));
			v=pos[i][(a+siz-1)%siz];
			if(dis2[u]>dis[v]+(u>v?(n-(u-v)):(v-u)))
			{
				dis2[u]=dis[v]+(u>v?(n-(u-v)):(v-u));
				dir[u]=1;
				ed[u]=v;
			}
		}
	}
	
	printf("%d\n",dis[0]);
	int now=s;
	for(int i=0;i<m;)
	{
		Move(now,path[i==0?0:now]);
		now=path[i==0?0:now];
		i++;
		
		int id=-1;
		for(int a=0;a<(int)pos[i].size();a++)
			if(pos[i][a]==now)
			{id=a;break;}
		int tmp=now;
		if(pos[i].size()==1)
			continue;
		for(int a=(id+dir[tmp]+pos[i].size())%pos[i].size();;a=(a+dir[tmp]+pos[i].size())%pos[i].size())
		{
			Move(now,pos[i][a]);
			now=pos[i][a];
			if(pos[i][a]==ed[tmp])
				break;
		}
	}
	
	return 0;
}
