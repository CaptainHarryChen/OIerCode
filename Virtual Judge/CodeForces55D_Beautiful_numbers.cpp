#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXD=19,MAXN=10,MAXLCM=2520,LCMCNT=48;
const int LCMS[LCMCNT]={1,2,3,4,5,6,7,8,9,10,12,14,15,18,20,21,24,28,30,35,36,40,42,45,56,60,63,70,72,84,90,105,120,126,140,168,180,210,252,280,315,360,420,504,630,840,1260,2520};
long long dp[MAXD][LCMCNT][MAXLCM];
int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}
int lcm(int a,int b)
{return a/gcd(a,b)*b;}
void init()
{
	for(int l=0;l<LCMCNT;l++)
		for(int p=0;p<MAXLCM;p+=LCMS[l])
			dp[0][l][p]=1LL;
	for(int i=1;i<MAXD;i++)
		for(int l=0;l<LCMCNT;l++)
			for(int r=0;r<MAXLCM;r++)
				for(int k=0;k<MAXN;k++)
				{
					int nl=lower_bound(LCMS,LCMS+LCMCNT,k?lcm(LCMS[l],k):LCMS[l])-LCMS;
					dp[i][l][r]+=dp[i-1][nl][(r*10+k)%MAXLCM];
				}
}
long long solve(long long x)
{
	long long ret=0;
	char num[MAXD];
	sprintf(num,"%I64d",x);
	int len=strlen(num),tl=1,tmp=0;
	for(int i=len;i>0;i--)
	{
		for(int j=0;j<num[len-i]-'0';j++)
		{
			int nl=lower_bound(LCMS,LCMS+LCMCNT,j?lcm(tl,j):tl)-LCMS;
			ret+=dp[i-1][nl][(tmp*10+j)%MAXLCM];
		}
		tl=(num[len-i]-'0')?lcm(tl,num[len-i]-'0'):tl;
		tmp=(tmp*10+num[len-i]-'0')%MAXLCM;
	}
	return ret;
}
int main()
{
	init();
	int T;
	long long l,r;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%I64d%I64d",&l,&r);
		printf("%I64d\n",solve(r+1)-solve(l));
	}
	return 0;
}
