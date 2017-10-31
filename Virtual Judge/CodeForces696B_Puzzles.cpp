#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;
int n;
int fa[MAXN];
vector<int>son[MAXN];
int size[MAXN];
double ans[MAXN];
double C(int m,int n)
{
	double res=1.0;
	for(int i=1;i<=m;i++)
		res=res*(m-i+1)/i;
	return res;
}
void prepare(int u)
{
	size[u]=1;
	for(int i=0;i<(int)son[u].size();i++)
	{
		prepare(son[u][i]);
		size[u]+=size[son[u][i]];
	}
}
void solve(int u)
{
	for(int i=0;i<(int)son[u].size();i++)
	{
		ans[son[u][i]]=ans[u]+1.0+(size[u]-1-size[son[u][i]])/2.0;
		solve(son[u][i]);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",fa+i);
		son[fa[i]].push_back(i);
	}
	prepare(1);
	ans[1]=1.0;
	solve(1);
	for(int i=1;i<n;i++)
		printf("%.7lf ",ans[i]);
	printf("%.7lf\n",ans[n]);
	return 0;
}
