#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n,m,k;
long long a[MAXN],b[MAXN],l;
int cnt[MAXN];

int main()
{
	scanf("%d%d%I64d",&n,&k,&l);
	m=n*k;
	for(int i=1;i<=m;i++)
		scanf("%I64d",a+i);
	sort(a+1,a+m+1);
	memcpy(b,a,sizeof a);
	int nm=unique(b+1,b+m+1)-b-1;
	for(int i=1,j=1;i<=nm;i++)
		for(;j<=m&&a[j]==b[i];j++)
			cnt[i]++;
	int pos=0,sum=0;
	for(int i=nm;i>0;i--)
		if(b[i]-b[1]>l)
			sum+=cnt[i],pos=i;
		else
			break;
	
	if(m-sum<n)
	{
		puts("0");
		return 0;
	}
	
	sum=m-sum;
	
	long long ans=0;
	int bar=1,fil=0;
	for(int i=1;i<=sum;i++)
	{
		if(bar>n)break;
		if(fil==0)
		{
			ans+=a[i];
			fil++;
			if(fil==k)
			{fil=0;bar++;}
			continue;
		}
		if(sum-i<n-bar)
		{
			bar++;
			fil=0;
			i--;
			continue;
		}
		fil++;
		if(fil==k)
		{fil=0;bar++;}
	}
	
	printf("%I64d\n",ans);
	
	return 0;
}
