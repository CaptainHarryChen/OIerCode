#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1005
int R,N;
int pos[MAXN];
int main()
{
	while(1)
	{
		scanf("%d%d",&R,&N);
		if(R==-1&&N==-1)
			break;
		for(int i=1;i<=N;i++)
			scanf("%d",pos+i);
		sort(pos+1,pos+N+1);
		int ans=0,now=1,j,k;
		while(now<=N)
		{
			for(j=now+1;j<=N;j++)
				if(pos[j]-pos[now]>R)
				{j--;break;}
			ans++;
			for(k=j+1;k<=N;k++)
				if(pos[k]-pos[j]>R)
				{now=k;break;}
			if(k>N)break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
