#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
const int MAXN=55;

class CirclesGame {
public:
	string whoCanWin(vector<int>&,vector<int>&,vector<int>&);
};

vector<int> son[MAXN];
int fa[MAXN];
int sg[MAXN];
int dfn[MAXN],ti[MAXN],dfc;
bool vis[MAXN];

void DP(int u)
{
	dfn[u]=++dfc;
	ti[dfc]=u;
	for(int i=0;i<(int)son[u].size();i++)
		DP(son[u][i]);
	if(son[u].size()==0U)
	{
		sg[u]=1;
		return;
	}
	fill(vis,vis+MAXN,false);
	for(int i=dfn[u];i<=dfc;i++)
	{
		int v=ti[i],temp=0,last=-1;
		while(dfn[v]>=dfn[u])
		{
			for(int j=0;j<(int)son[v].size();j++)
				if(son[v][j]!=last)
					temp^=sg[son[v][j]];
			last=v;
			v=fa[v];
		}
		vis[temp]=true;
	}
	for(int i=0;i<MAXN;i++)
		if(!vis[i])
		{
			sg[u]=i;
			return;
		}
}

string CirclesGame::whoCanWin(vector<int> &x,vector<int> &y,vector<int> &r)
{
	int n=x.size();
	fill(fa,fa+n,-1);
	for(int i=0;i<n;i++)
	{
		int mn=0x7FFFFFFF;
		for(int j=0;j<n;j++)
			if(i!=j&&r[j]>r[i]&&(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<r[j]*r[j])
			{
				if(mn>r[j])
					mn=r[j],fa[i]=j;
			}
		son[fa[i]].push_back(i);
	}
	int ans=0;
	for(int i=0;i<n;i++)
		if(fa[i]==-1)
		{
			DP(i);
			ans^=sg[i];
		}
	if(ans)
		return "Alice";
	return "Bob";
}

CirclesGame CG;
vector<int> a,b,c;
int main()
{
	int n;
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		a.push_back(x);
	}
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		b.push_back(x);
	}
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		c.push_back(x);
	}
	cout<<CG.whoCanWin(a,b,c)<<endl;
	
	return 0;
}
