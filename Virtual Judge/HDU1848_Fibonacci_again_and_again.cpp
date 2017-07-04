#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
using std::swap;
#define MAXN 1005
int g[MAXN];
int fib[20],fib_cnt;
bool vis[MAXN];
int main()
{
	int m,n,p;
	int a=1,b=1;
	while(a<MAXN)
	{
		fib[fib_cnt++]=a;
		b=a+b;
		swap(a,b);
	}
	g[0]=0;
	for(int i=1,j;i<MAXN;i++)
	{
		memset(vis,0,sizeof vis);
		for(j=0;j<fib_cnt&&fib[j]<=i;j++)
			vis[g[i-fib[j]]]=1;
		for(j=0;vis[j];j++);
		g[i]=j;
	}
	while(1)
	{
		scanf("%d%d%d",&m,&n,&p);
		if(!m&&!n&&!p)break;
		if(((g[m]^g[n])^g[p])==0)
			printf("Nacci\n");
		else
			printf("Fibo\n");
	}
	return 0;
}
