#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXN 200005
int A[MAXN][2];
int cnts[55];
int main()
{
	int n,k,p;
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i][0],&A[i][1]);
	int a=0,b=0;
	for(int i=1;i<=n;i++)
		if(A[i][1]<=p)
			memset(cnts,0,sizeof cnts);
		else
			a+=(cnts[A[i][0]]++);
	memset(cnts,0,sizeof cnts);
	for(int i=1;i<=n;i++)
		b+=(cnts[A[i][0]]++);
	printf("%d\n",b-a);
	return 0;
}
