#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=50005;

int n,st,x;
int best;
int val[MAXN],nxt[MAXN];

int main()
{
	srand(2018);
	memset(val,-1,sizeof val);
	memset(nxt,0,sizeof nxt);
	scanf("%d%d%d",&n,&st,&x);
	best=st;
	
	for(int i=1;i<=min(n,230);i++)
	{
		int pos=(rand()*rand())%n+1;
		if(val[pos]!=-1)
		{
			i--;
			continue;
		}
		printf("? %d\n",pos);
		fflush(stdout);
		scanf("%d%d",&val[pos],&nxt[pos]);
		if(val[pos]<=x&&val[best]<val[pos])
			best=pos;
	}
	
	while(true)
	{
		if(val[best]==-1)
		{
			printf("? %d\n",best);
			fflush(stdout);
			scanf("%d%d",&val[best],&nxt[best]);
		}
		if(nxt[best]==-1)
			break;
		if(val[best]>=x)
			break;
		best=nxt[best];
	}
	if(val[best]<x)
		printf("! -1\n");
	else
		printf("! %d\n",val[best]);
	fflush(stdout);
	
	return 0;
}
