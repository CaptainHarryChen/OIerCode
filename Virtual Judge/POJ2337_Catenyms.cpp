#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=30,MAXE=1005;
int indeg[MAXN],outdeg[MAXN];
string words[MAXE];
typedef pair<int,int> Edge;
vector<Edge> V[MAXN];
int path[MAXE],top;
bool vis[MAXE];
void euler(int id)
{
	int sz=V[id].size();
	for(int i=0;i<sz;i++)
		if(!vis[V[id][i].first])
		{
			vis[V[id][i].first]=true;
			euler(V[id][i].second);
			path[++top]=V[id][i].first;
		}
}
int main()
{
	int T,n,u,v,st,cntS,cntT;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			cin>>words[i];
		sort(words+1,words+n+1);
		memset(indeg,0,sizeof indeg);
		memset(outdeg,0,sizeof outdeg);
		for(int i=0;i<26;i++)
			V[i].clear();
		for(int i=1;i<=n;i++)
		{
			u=words[i][0]-'a';
			v=words[i][words[i].size()-1]-'a';
			V[u].push_back(Edge(i,v));
			indeg[v]++;
			outdeg[u]++;
		}
		st=-1;
		cntS=0;
		cntT=0;
		for(int i=0;i<26;i++)
		{
			if(indeg[i]-outdeg[i]>1||indeg[i]-outdeg[i]<-1)
			{
				cntS=cntT=2;
				break;
			}
			if(indeg[i]-outdeg[i]==1)
			{
				cntT++;
				if(cntT>1)
					break;
			}
			if(indeg[i]-outdeg[i]==-1)
			{
				cntS++;
				if(cntS>1)
					break;
				st=i;
			}
		}
		if(cntS>1||cntT>1||cntS!=cntT)
		{
			printf("***\n");
			continue;
		}
		if(st==-1)
			for(int i=0;i<26;i++)
				if(indeg[i]>0)
				{
					st=i;
					break;
				}
		top=0;
		memset(vis,0,sizeof vis);
		euler(st);
		if(top<n)
		{
			printf("***\n");
			continue;
		}
		for(int i=top;i>1;i--)
			cout<<words[path[i]]<<'.';
		cout<<words[path[1]]<<endl;
	}
	return 0;
}
