#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
const int MAXN=3005,MAXM=20005;
struct curse
{
	int x,y,z;
	curse(){}
	curse(int _x,int _y,int _z)
	{x=_x;y=_y;z=_z;}
	bool operator < (const curse &t)const
	{
		if(x<t.x)return true;
		if(x>t.x)return false;
		if(y<t.y)return true;
		if(y>t.y)return false;
		return z<t.z;
	}
};
int E[MAXM*2][2];
vector<int>key[MAXN];
map<curse,bool>cs;
int dis[MAXM*2],path[MAXM*2],ans[MAXM*2];
queue<int>Q;
void BFS()
{
	memset(dis,0x3F,sizeof dis);
	for(int i=0;i<(int)key[1].size();i++)
	{
		dis[key[1][i]]=1;
		Q.push(key[1][i]);
	}
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		int u=E[t][0],v=E[t][1];
		for(int i=0;i<(int)key[v].size();i++)
		{
			int tt=key[v][i];
			if(dis[tt]>dis[t]+1&&!cs[curse(u,v,E[tt][1])])
			{
				dis[tt]=dis[t]+1;
				path[tt]=t;
				Q.push(tt);
			}
		}
	}
}
int main()
{
	int n,m,k,a,b,c;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		E[i*2-1][0]=a;E[i*2-1][1]=b;
		E[i*2][0]=b;E[i*2][1]=a;
		key[a].push_back(i*2-1);
		key[b].push_back(i*2);
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		cs[curse(a,b,c)]=true;
	}
	BFS();
	int len=0x3F3F3F3F,id,l;
	for(int i=1;i<=2*m;i++)
		if(E[i][1]==n&&len>dis[i])
		{
			len=dis[i];
			id=i;
		}
	if(len==0x3F3F3F3F)
	{
		puts("-1");
		return 0;
	}
	printf("%d\n",len);
	l=len;
	while(id)
	{
		ans[l]=E[id][0];
		id=path[id];
		l--;
	}
	for(int i=1;i<=len;i++)
		printf("%d ",ans[i]);
	printf("%d\n",n);
	return 0;
}
