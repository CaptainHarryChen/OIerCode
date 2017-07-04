#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,p;
bool num[125005],none;
struct print
{
	int a,b;
}arr[100000];
bool xiaoyu(print a,print b)
{
	if(a.b<b.b)
		return 1;
	if(a.b==b.b)
		return a.a<b.a;
	return 0;
}
void shengcheng()
{
	int q[63005],cnt=0;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			q[cnt++]=i*i+j*j;
	sort(q,q+cnt);
	cnt=0;
	for(int i=0;i<=m*m*2;i++)
	{
		if(cnt!=0&&q[cnt-1]==q[cnt])
		{cnt++;i--;continue;}
		if(i==q[cnt])
		{
			num[i]=1;
			cnt++;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	shengcheng();
	for(int i=0;i<=2*m*m;i++)
	{
		if(!num[i])continue;
		bool f=1;
		for(int j=i+1;j<=2*m*m;j++)
		{
			if(!num[j])continue;
			int end=i+(j-i)*(n-1);
			if(end>2*m*m&&j==i+1)
			{f=0;break;}
			if(end>2*m*m)
				break;
			bool ff=1;
			for(int k=2;k<n;k++)
			{
				int s=i+k*(j-i);
				if(!num[s])
				{ff=0;break;}
			}
			if(!ff)
				continue;
			arr[p].a=i;arr[p++].b=j-i;
			none=1;
		}
		if(!f)
			break;
	}
	if(!none)
	{printf("NONE\n");return 0;}
	sort(arr,arr+p,xiaoyu);
	for(int i=0;i<p;i++)
		printf("%d %d\n",arr[i].a,arr[i].b);
	return 0;
}
