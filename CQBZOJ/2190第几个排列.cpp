#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,shuzi[10],count,nm,q,quanzhi[12]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800};
char num[10],tnum[10];
bool f[400000];
int zhuanhuan(char x[])
{
	int cnt=0,sum=0;
	bool ff[10]={0};
	for(int i=0;i<10;i++)
	{
		cnt=0;
		for(int j=i+1;j<9;j++)
			if(x[j]<x[i]&&ff[j]==0)
				cnt++;
		ff[i]=1;
		sum+=cnt*quanzhi[n-i-1];
	}
	return sum;
}
int zhuanhuan2(char x[])
{
	int sum=0;
	for(int i=0;i<n;i++)
	{sum*=10;sum+=x[i];}
	return sum;
}
void dfs(int p)
{
	if(p==n)
	{
		int s=zhuanhuan(tnum);
		if(f[s]==0&&zhuanhuan2(tnum)<nm)
			count++;
		f[s]=1;
		return;
	}
	for(int i=0;i<10;i++)
		if(shuzi[i]!=0)
		{
			tnum[q++]=i;
			shuzi[i]--;
			dfs(p+1);
			shuzi[i]++;
			tnum[--q]=0;
		}
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%c",&num[i]);
		if(num[i]>'9'||num[i]<'0'){i--;continue;}
		num[i]-='0';
		shuzi[(int)num[i]]++;
	}
	nm=zhuanhuan2(num);
	dfs(0);
	printf("%d\n",count);
	return 0;
}
