#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXM 505
#define MAXN INF 200000000
using namespace std;
int m,k,book[MAXM],people[MAXM][2];
void Find_X(int L,int R)
{
	int mid=(L+R)>>1,cnt=1,i,j;
	for(i=m,j=0;i>=1;i--)
	{
		if(j+book[i]<=mid)
		{
			if(j==0)people[cnt][1]=i;
			j+=book[i];
		}
		else
		{j=0;i++;people[cnt][0]=i;cnt++;}
	}
	people[cnt][0]=i+1;
	if(L==R)
	{
		for(int i=k;i>=1;i--)
			printf("%d %d\n",people[i][0],people[i][1]);
		exit(0);
	}
	if(cnt<=k)Find_X(L,mid);
	else if(cnt>k)Find_X(mid+1,R);
}
int main()
{
	scanf("%d%d",&m,&k);
	int s=0,maxb=0;
	for(int i=1;i<=m;i++)
	{scanf("%d",&book[i]);s+=book[i];maxb=max(maxb,book[i]);}
	Find_X(maxb,s);
	return 0;
}
