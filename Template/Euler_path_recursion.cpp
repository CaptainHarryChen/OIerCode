#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=505,MAXE=1100;
int E[MAXN][MAXN];
int ans[MAXE],cnt;
int deg[MAXN],n,m;
int stack[MAXE],top;
void find_circle(int S)
{
	int x=S;
	bool flag=true;
	while(flag)
	{
		stack[++top]=x;
		flag=false;
		for(int i=1;i<=n;i++)
			if(E[x][i]>0)
			{
				E[x][i]--;
				E[i][x]--;
				x=i;
				flag=true;
				break;
			}
	}
	if(stack[top]==S)
		top--;
}
void euler(int S)
{
	find_circle(S);
	while(top)
	{
		ans[++cnt]=stack[top];
		top--;
		find_circle(stack[top+1]);
	}
}
int main()
{
	freopen("Euler_path_recursion_data.in","r",stdin);
	int a,b,S,T;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		E[a][b]++;
		E[b][a]++;
		deg[a]++;
		deg[b]++;
		n=max(n,a);
		n=max(n,b);
	}
	S=0;T=0;
	for(int i=1;i<=n;i++)
		if(deg[i]&1)
		{
			if(S)
			{
				T=i;
				break;
			}
			S=i;
		}
	if(S)
		euler(S);
	else
		euler(1);
	for(int i=cnt;i>=1;i--)
		printf("%d\n",ans[i]);
	if(!S)
		printf("1\n");
	return 0;
}
