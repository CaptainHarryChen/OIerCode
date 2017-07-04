#include<cstdio>
#include<iostream>
#include<cstring>
#include<climits>
using namespace std;
int n,m,s,t,arr[505][505],u[505],dis[505],jilu[505],print[505],p;
int main()
{
   cin>>n>>m;
	int a,b,min;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		arr[a-1][b-1]=1;
	}
	cin>>s>>t;
	memset(dis,127,sizeof(dis));
	dis[s-1]=0;
	min=s-1;
	for(int cnt=0;cnt<n;cnt++)
	{
		u[min]=1;
		for(int i=0;i<n;i++)
		{
			if(arr[min][i]!=0&&dis[min]+arr[min][i]<dis[i])
			{
				dis[i]=arr[min][i]+dis[min];
				jilu[i]=min;
			}
		}
		int themin=INT_MAX;
		for(int i=0;i<n;i++)
            if(u[i]==0&&dis[i]<themin)
			{
				min=i;
				themin=dis[i];
			}
		if(themin==INT_MAX)break;
	}
	int i=t-1;
	while(i!=s-1)
	{
		print[p++]=i;
		i=jilu[i];
	}
	print[p++]=s-1;
	if(dis[t-1]==2139062143)
	{
		printf("no solution\n");
		return 0;
	}
	printf("%d\n",dis[t-1]);
	for(int j=p-1;j>0;j--)
		printf("%d ",print[j]+1);
	printf("%d\n",print[0]+1);
	return 0;
}
