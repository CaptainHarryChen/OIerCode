#include<cstdio>
#include<cstring>
#define MAXN 105
#define MAXW 10005
int E[2][MAXW];
int W[MAXN],p[MAXN];
int main()
{
	int N,S,cnt;
	while(~scanf("%d",&N))
	{
		S=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&W[i]);
			S+=W[i];
		}
		memset(E,0,sizeof E);
		E[1][W[1]]=E[1][0]=1;
		for(int i=2;i<=N;i++)
		{
			memset(E[i&1],0,sizeof(int)*MAXW);
			for(int j=0;j<=S;j++)
			{
				E[i&1][j]+=E[(i+1)&1][j];
				E[i&1][j+W[i]]+=E[(i+1)&1][j];
				if(j>W[i])E[i&1][j-W[i]]+=E[(i+1)&1][j];
				else E[i&1][W[i]-j]+=E[(i+1)&1][j];
			}
		}
		cnt=0;
		for(int i=1;i<=S;i++)
			if(!E[N&1][i])
			{p[cnt++]=i;}
		printf("%d\n",cnt);
		for(int i=0;i<cnt-1;i++)
			printf("%d ",p[i]);
		if(cnt)printf("%d\n",p[cnt-1]);
	}
	return 0;
}#include<cstdio>
#include<cstring>
#define MAXN 105
#define MAXW 10005
int E[2][MAXW];
int W[MAXN],p[MAXN];
int main()
{
	int N,S,cnt;
	while(~scanf("%d",&N))
	{
		S=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&W[i]);
			S+=W[i];
		}
		memset(E,0,sizeof E);
		E[1][W[1]]=E[1][0]=1;
		for(int i=2;i<=N;i++)
		{
			memset(E[i&1],0,sizeof(int)*MAXW);
			for(int j=0;j<=S;j++)
			{
				E[i&1][j]+=E[(i+1)&1][j];
				E[i&1][j+W[i]]+=E[(i+1)&1][j];
				if(j>W[i])E[i&1][j-W[i]]+=E[(i+1)&1][j];
				else E[i&1][W[i]-j]+=E[(i+1)&1][j];
			}
		}
		cnt=0;
		for(int i=1;i<=S;i++)
			if(!E[N&1][i])
			{p[cnt++]=i;}
		printf("%d\n",cnt);
		for(int i=0;i<cnt-1;i++)
			printf("%d ",p[i]);
		if(cnt)printf("%d\n",p[cnt-1]);
	}
	return 0;
}