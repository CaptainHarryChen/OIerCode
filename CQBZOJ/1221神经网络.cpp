#include<cstdio>
#include<iostream>
using namespace std;
int n,p,w[205][205],c[205], u[205];
bool shuru[205],shuchu[205];
int main()
{
	cin>>n>>p;
	for(int i=0;i<n;i++)
		scanf("%d%d",&c[i],&u[i]);
	int a,b,ww;
	for(int i=0;i<p;i++)
	{
		scanf("%d%d%d",&a,&b,&ww);
		w[a-1][b-1]=ww;
		shuru[b-1]=1;
		shuchu[a-1]=1;
	}
	for(int i=0;i<n;i++)
	{
		if(!shuru[i]||c[i]<0)continue;
		int sum=0;
		for(int j=0;j<n;j++)
			if(w[j][i]!=0&&c[j]>=0)
				sum+=w[j][i]*c[j];
		sum-=u[i];
		c[i]=sum;
	}
	bool f=0;
	for(int i=0;i<n;i++)
	{
		if(shuchu[i]||c[i]<=0)continue;
		f=1;
		printf("%d %d\n",i+1,c[i]);
	}
	if(!f)
		printf("NULL\n");
	return 0;
}
