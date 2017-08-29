#include<cstdio>
#include<cstring>
const int MAXN=100010;
const int pow10[10]={1,10,100,1000,10000,100000,1000000};
int sta[MAXN*10],top,pt;
char path[MAXN*10];
bool vis[MAXN*10];
int n;
void dfs(int id)
{
	int x;
	for(int i=0;i<10;i++)
	{
		x=id*10+i;
		if(vis[x])
			continue;
		vis[x]=true;
		dfs(x%pow10[n-1]);
	}
	path[++top]=id;
}
void find_circle(int S)
{
	int id=S,x;
	bool flag=true;
	while(flag)
	{
		flag=false;
		sta[++top]=id;
		for(int i=0;i<10;i++)
		{
			x=id*10+i;
			if(vis[x])
				continue;
			vis[x]=true;
			flag=true;
			id=x%pow10[n-1];
			break;
		}
	}
	top--;
}
void euler()
{
	find_circle(0);
	int temp;
	while(top)
	{
		temp=sta[top];
		top--;
		path[++pt]=temp%10;
		find_circle(temp);
	}
}
int main()
{
	while(true)
	{
		top=0;
		pt=0;
		memset(vis,0,sizeof vis);
		scanf("%d",&n);
		if(n==0)
			break;
		if(n==1)
		{
			printf("0123456789\n");
			continue;
		}
		//dfs(0);
		/*for(int i=1;i<n;i++)
			printf("0");
		for(int i=top-1;i>0;i--)
			printf("%d",path[i]%10);
		puts("");*/
		
		euler();
		for(int i=1;i<n;i++)
			printf("0");
		for(int i=pt-1;i>0;i--)
			printf("%d",path[i]);
		puts("0");
	}
	return 0;
}
