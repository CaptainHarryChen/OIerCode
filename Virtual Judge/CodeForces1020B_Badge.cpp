#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n,p[MAXN];
int vis[MAXN];
int stk[MAXN],top;
int ans[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			int u=i;
			top=0;
			while(!vis[u])
			{
				vis[u]=i;
				stk[++top]=u;
				u=p[u];
			}
			if(vis[u]==i)
			{
				do
				{
					ans[stk[top]]=stk[top];
					top--;
				}while(stk[top+1]!=u);
			}
			while(top)
				ans[stk[top--]]=ans[u];
		}
		
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
	
	return 0;
}