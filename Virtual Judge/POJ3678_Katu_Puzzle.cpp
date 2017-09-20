#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=1005,MAXM=1000005;
vector<int>G[MAXN*2];
int S[MAXN*2],top;
int col[MAXN*2];
int cc[MAXN*2];
bool color(int u)
{
	if(col[u])
		return col[u]==1;
	if(cc[u]==2)
		return false;
	col[u]=1;
	if(cc[u^1]==1)
		return false;
	col[u^1]=2;
	S[++top]=u;
	for(int i=0;i<(int)G[u].size();i++)
		if(!color(G[u][i]))
			return false;
	return true;
}
int main()
{
	int n,m,a,b,c;
	char op[5];
	scanf("%d%d",&n,&m);
	bool flag=true;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%s",&a,&b,&c,op);
		if(op[0]=='A')
		{
			if(c)
			{
				if(cc[a*2]==1||cc[b*2]==1)
				{
					flag=false;
					break;
				}
				cc[a*2]=cc[b*2]=2;
				if(cc[a*2+1]==2||cc[b*2+1]==2)
				{
					flag=false;
					break;
				}
				cc[a*2+1]=cc[b*2+1]=1;
			}
			else
			{
				G[a*2+1].push_back(b*2);
				G[b*2+1].push_back(a*2);
			}
		}
		if(op[0]=='O')
		{
			if(c)
			{
				G[a*2].push_back(b*2+1);
				G[b*2].push_back(a*2+1);
			}
			else
			{
				if(cc[a*2]==2||cc[b*2]==2)
				{
					flag=false;
					break;
				}
				cc[a*2]=cc[b*2]=1;
				if(cc[a*2+1]==1||cc[b*2+1]==1)
				{
					flag=false;
					break;
				}
				cc[a*2+1]=cc[b*2+1]=2;
			}
		}
		if(op[0]=='X')
		{
			if(c)
			{
				G[a*2].push_back(b*2+1);
				G[b*2+1].push_back(a*2);
				G[a*2+1].push_back(b*2);
				G[b*2].push_back(a*2+1);
			}
			else
			{
				G[a*2].push_back(b*2);
				G[b*2].push_back(a*2);
				G[a*2+1].push_back(b*2+1);
				G[b*2+1].push_back(a*2+1);
			}
		}
	}
	for(int i=0;i<2*n;i++)
		if(col[i]==0)
		{
			top=0;
			if(!color(i))
			{
				while(top)
				{
					col[S[top]]=0;
					col[S[top]^1]=0;
					top--;
				}
				if(!color(i^1))
				{
					flag=false;
					break;
				}
			}
		}
	if(flag)
		puts("YES");
	else
		puts("NO");
	return 0;
}
