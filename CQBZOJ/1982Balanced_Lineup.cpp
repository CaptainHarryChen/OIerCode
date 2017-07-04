#include<cstdio>
#include<iostream>
using namespace std;
#define MAXN 50005
int N,Q,A[MAXN],Max[MAXN][25],Min[MAXN][25];
int Log(int x)
{
	int j;
	for(j=0;(1<<j)<=x;j++);
	return j-1;
}
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	int k=Log(N);
	for(int j=0;j<=k;j++)
		for(int i=1;i-1+(1<<j)<=N;i++)
		{
			if(!j)
			{Max[i][j]=Min[i][j]=A[i];continue;}
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
		}
	for(int i=1,a,b,p,_min,_max;i<=Q;i++)
	{
		scanf("%d%d",&a,&b);
		p=Log(b-a+1);
		_min=min(Min[a][p],Min[b-(1<<p)+1][p]);
		_max=max(Max[a][p],Max[b-(1<<p)+1][p]);
		printf("%d\n",_max-_min);
	}
	return 0;
}
