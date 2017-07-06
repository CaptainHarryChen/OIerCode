#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXL=1000000005,MAXN=50005;
int rock[MAXN],L,N,M;
int main()
{
	scanf("%d%d%d",&L,&N,&M);
	for(int i=1;i<=N;i++)
		scanf("%d",rock+i);
	sort(rock+1,rock+N+1);
	int l=1,r=L,mid,cnt,last;
	while(l<r)
	{
		mid=(l+r+1)/2;
		cnt=0;
		last=0;
		for(int i=1;i<=N&&cnt<=M;i++)
			if(rock[i]-last<mid)
				cnt++;
			else
				last=rock[i];
		if(cnt>M)
			r=mid-1;
		else
			l=mid;
	}
	printf("%d\n",l);
	return 0;
}
