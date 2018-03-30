#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
const int MAXN=55;

class GameWithTree {
public:
	string winner(vector<int>&,string col);
};

vector<int> son[MAXN];
vector<int> fa;
string col;
int sg[MAXN];
int dep[MAXN];

void Dfs(int u)
{
	dep[u]=0;
	int temp=0;
	sg[u]=0;
	for(int i=0;i<(int)son[u].size();i++)
	{
		Dfs(son[u][i]);
		dep[u]=max(dep[u],dep[son[u][i]]+1);
		temp^=sg[son[u][i]];
	}
	if(son[u].size()==0U)
		dep[u]=1;
	if(col[u]=='W')
		sg[u]=1<<(dep[u]-1);
	sg[u]+=temp;
}

string GameWithTree::winner(vector<int> &fa,string col)
{
	int n=fa.size()+1;
	::fa.resize(n);
	::col=col;
	::fa[0]=-1;
	for(int i=0;i<n-1;i++)
	{
		::fa[i+1]=fa[i];
		son[::fa[i+1]].push_back(i+1);
	}
	Dfs(0);
	if(sg[0])
		return "Masha";
	return "Petya";
}

GameWithTree GWT;
vector<int> f;
string c;
int main()
{
	int n;
	cin>>n;
	n++;
	for(int i=1,x;i<n;i++)
	{
		cin>>x;
		f.push_back(x);
	}
	cin>>c;
	cout<<GWT.winner(f,c)<<endl;
	
	return 0;
}
