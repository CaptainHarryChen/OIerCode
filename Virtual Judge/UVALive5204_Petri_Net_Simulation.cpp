#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
const int MAXN=105;

int n;
int tran[MAXN][MAXN];
int tok[MAXN];

bool enable(int id)
{
	for(int i=1;i<=n;i++)
		if(tran[id][i]+tok[i]<0)
			return false;
	return true;
}
void run(int id)
{
	for(int i=1;i<=n;i++)
		tok[i]+=tran[id][i];
}

int main()
{
	int m,round;
	for(int Case=1;;Case++)
	{
		scanf("%d",&n);
		if(n==0)break;
		for(int i=1;i<=n;i++)
			scanf("%d",&tok[i]);
		memset(tran,0,sizeof tran);
		scanf("%d",&m);
		for(int i=1,x;i<=m;i++)
			while(scanf("%d",&x),x)
				tran[i][abs(x)]+=x/abs(x);
		scanf("%d",&round);
		int dead=-1;
		for(int r=1;r<=round;r++)
		{
			bool flag=false;
			for(int tr=1;tr<=m;tr++)
				if(enable(tr))
				{
					run(tr);
					flag=true;
					break;
				}
			if(!flag)
			{
				dead=r-1;
				break;
			}
		}
		printf("Case %d: ",Case);
		if(dead==-1)
			printf("still live after %d transitions\n",round);
		else
			printf("dead after %d transitions\n",dead);		printf("Places with tokens:");
		for(int i=1;i<=n;i++)
			if(tok[i])
				printf(" %d (%d)",i,tok[i]);
		printf("\n\n");
	}
	return 0;
}
