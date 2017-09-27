#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXM=400005;
struct Edge
{
	int u,v,id;
};
struct UFS
{
	int S[MAXN];
	void clear()
	{
		memset(S,0,sizeof S);
	}
	int Find(int x)
	{
		if(S[x]==0)
			return x;
		return S[x]=Find(S[x]);
	}
	void Union(int a,int b)
	{
		int r1=Find(a),r2=Find(b);
		if(r1==r2)return;
		S[r1]=r2;
	}
};
Edge E[MAXM];
UFS S;
bool used[MAXM];
int ids[MAXN],idt[MAXN];
bool viss[MAXN],vist[MAXN];
int main()
{
	int n,m,s,t,ds,dt,dds,ddt,r1,r2,cnt;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&E[i].u,&E[i].v);
	scanf("%d%d%d%d",&s,&t,&ds,&dt);
	dds=ds,ddt=dt;
	for(int i=1;i<=m;i++)
	{
		if(E[i].u==s||E[i].u==t||E[i].v==s||E[i].v==t)
			continue;
		r1=S.Find(E[i].u);
		r2=S.Find(E[i].v);
		if(r1!=r2)
			used[i]=1;
		S.Union(r1,r2);
	}
	for(int i=1;i<=m;i++)
	{
		if(E[i].u!=s&&E[i].v!=s)
			continue;
		if(E[i].v==s)
			swap(E[i].u,E[i].v);
		r1=S.Find(E[i].v);
		if(!viss[r1])
			ids[r1]=i;
		viss[r1]=1;
	}
	for(int i=1;i<=m;i++)
	{
		if(E[i].u!=t&&E[i].v!=t)
			continue;
		if(E[i].v==t)
			swap(E[i].u,E[i].v);
		r2=S.Find(E[i].v);
		if(!vist[r2])
			idt[r2]=i;
		vist[r2]=1;
	}
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(i==s||i==t)
			continue;
		if(viss[i]&&!vist[i])
			ds--;
		if(!viss[i]&&vist[i])
			dt--;
		if(viss[i]&&vist[i])
			cnt++;
	}
	if(ds>0&&dt>0&&((cnt>0&&cnt+1<=ds+dt)||(viss[t]&&cnt<=ds+dt-2)))
	{
		printf("Yes\n");
		for(int i=1;i<=m;i++)
			if(used[i])
				printf("%d %d\n",E[i].u,E[i].v);
		if(cnt>0&&cnt+1<=ds+dt)
		{
			bool flag=false;
			for(int i=1;i<=n;i++)
				if(i!=s&&i!=t)
				{
					if(viss[i]&&vist[i])
					{
						if(!flag)
						{
							printf("%d %d\n%d %d\n",E[ids[i]].u,E[ids[i]].v,E[idt[i]].u,E[idt[i]].v);
							dds--,ddt--;
							flag=true;
						}
						else
						{
							if(dds>ddt)
							{
								printf("%d %d\n",E[ids[i]].u,E[ids[i]].v);
								dds--;
							}
							else
							{
								printf("%d %d\n",E[idt[i]].u,E[idt[i]].v);
								ddt--;
							}
						}
					}
					else if(viss[i])
					{
						printf("%d %d\n",E[ids[i]].u,E[ids[i]].v);
						dds--;
					}
					else if(vist[i])
					{
						printf("%d %d\n",E[idt[i]].u,E[idt[i]].v);
						ddt--;
					}
				}
		}
		else
		{
			printf("%d %d\n",s,t);
			dds--,ddt--;
			for(int i=1;i<=n;i++)
				if(i!=s&&i!=t)
				{
					if(viss[i]&&vist[i])
					{
						if(dds>ddt)
						{
							printf("%d %d\n",E[ids[i]].u,E[ids[i]].v);
							dds--;
						}
						else
						{
							printf("%d %d\n",E[idt[i]].u,E[idt[i]].v);
							ddt--;
						}
					}
					else if(viss[i])
					{
						printf("%d %d\n",E[ids[i]].u,E[ids[i]].v);
						dds--;
					}
					else if(vist[i])
					{
						printf("%d %d\n",E[idt[i]].u,E[idt[i]].v);
						ddt--;
					}
				}
		}
	}
	else
		printf("No\n");
	return 0;
}
