#include<cstdio>
#include<cmath>
const int MAXN=400005;
char s[MAXN];
int cnt[130];
int ods[130],odd;
char pr[MAXN];
bool solve(int n,int d)
{
	if((n/d)%2==0&&odd==0)
	{
		printf("%d\n",d);
		int ch=0;
		for(int i=1;i<=d;i++)
		{
			for(int j=1;j*2<=n/d;j++)
			{
				while(!cnt[ch])ch++;
				pr[j]=pr[n/d-j+1]=ch;
				cnt[ch]-=2;
			}
			printf("%s",pr+1);
			if(i==d)puts("");
			else printf(" ");
		}
		return true;
	}
	if((n/d)%2==1&&odd<=d&&(d-odd)%2==0)
	{
		printf("%d\n",d);
		int ch=0;
		for(int i=1;i<=d;i++)
		{
			if(odd)
			{
				pr[(n/d+1)/2]=ods[odd];
				cnt[ods[odd--]]--;
			}
			else if(!odd)
			{
				while(cnt[ch]<2)ch++;
				pr[(n/d+1)/2]=ch;
				cnt[ch]--;
				ods[++odd]=ch;
			}
			for(int j=1;j*2<=n/d;j++)
			{
				while(cnt[ch]<2)ch++;
				pr[j]=pr[n/d-j+1]=ch;
				cnt[ch]-=2;
			}
			printf("%s",pr+1);
			if(i==d)puts("");
			else printf(" ");
		}
		return true;
	}
	return false;
}
int main()
{
	int n;
	scanf("%d%s",&n,s);
	for(int i=0;i<n;i++)
		cnt[(int)s[i]]++;
	for(int i=0;i<128;i++)
		if(cnt[i]%2==1)
			ods[++odd]=i;
	for(int d=1;1LL*d*d<=1LL*n;d++)
	{
		if(n%d)continue;
		if(solve(n,d))
			return 0;
	}
	for(int d=sqrt(n);d>=1;d--)
	{
		if(n%d)continue;
		if(solve(n,n/d))
			return 0;
	}
	return 0;
}
