#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
const int MAXN=1005;
vector<int>G[MAXN];
stack<int>S;
int link[MAXN][2];
int col[MAXN];
bool color(int u)
{
	if(col[u])
		return col[u]==1;
	col[u]=1;
	col[u^1]=2;
	S.push(u);
	for(int i=0;i<(int)G[u].size();i++)
		if(!color(G[u][i]))
			return false;
	return true;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
		scanf("%d%d",link[i],link[i]+1);
	for(int i=0;i<m;i++)
		for(int j=0;j<i;j++)
			if((link[i][0]<link[j][0]&&link[j][0]<link[i][1]&&link[i][1]<link[j][1])
				||(link[j][0]<link[i][0]&&link[i][0]<link[j][1]&&link[j][1]<link[i][1]))
				{
					G[2*i].push_back(2*j+1);
					G[2*j].push_back(2*i+1);
					G[2*i+1].push_back(2*j);
					G[2*j+1].push_back(2*i);
				}
	bool flag=true;
	for(int i=0;i<2*m;i++)
		if(!col[i])
			if(!color(i))
			{
				while(!S.empty())
				{
					col[S.top()]=0;
					S.pop();
				}
				if(!color(i^1))
				{
					flag=false;
					break;
				}
			}
	if(flag)
		puts("panda is telling the truth...");
	else
		puts("the evil panda is lying again");
	return 0;
}
