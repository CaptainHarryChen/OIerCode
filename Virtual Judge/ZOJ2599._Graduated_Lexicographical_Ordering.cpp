#include<cstdio>
#include<cstring>
const int MAXD=20,MAXN=10,MAXSUM=180;
unsigned long long dp[MAXD][MAXSUM];
void init()
{
	dp[0][0]=1;
	for(int i=1;i<MAXD;i++)
		for(int j=0;j<MAXN;j++)
			for(int s=j;s<=9*i-9+j;s++)
				dp[i][s]+=dp[i-1][s-j];
}
void getranks(unsigned long long n,unsigned long long res[MAXSUM])
{
	memset(res,0,sizeof(unsigned long long)*MAXSUM);
	char num[MAXD];
	sprintf(num,"%llu",n);
	int len=strlen(num),tmp=0;
	for(int i=len;i>0;i--)
	{
		for(int j=0;j<num[len-i]-'0';j++)
			for(int s=j;s<=i*9-9+j;s++)
				res[s+tmp]+=dp[i-1][s-j];
		tmp+=num[len-i]-'0';
	}
	res[tmp]++;
}
unsigned long long getcnt(unsigned long long n,int ds)
{
	unsigned long long ret=0;
	char num[MAXD];
	sprintf(num,"%llu",n);
	int len=strlen(num);
	for(int i=len;i>0&&ds>0;i--)
		for(int j=0;j<num[len-i]-'0'&&ds>0;j++)
			ret+=dp[i-1][ds--];
	ret+=dp[0][ds];
	return ret;
}
unsigned long long getrank(unsigned long long n,unsigned long long k,int ds)
{
	char sn[MAXD],sk[MAXD];
	sprintf(sn,"%llu",n);
	sprintf(sk,"%llu",k);
	unsigned long long ret=0;
	for(int i=1;i<ds;i++)
		ret+=getcnt(n,i);
	if(k==0)
		return ret;
	int ln=strlen(sn),lk=strlen(sk);
	unsigned long long tmp=k*10LL;
	for(int i=lk+1;i<=ln;i++)
	{
		ret+=getcnt((tmp-1>n)?n:(tmp-1),ds)-dp[i-1][ds];
		tmp*=10LL;
	}
	tmp=k;
	for(int i=lk;i>0;i--)
	{
		ret+=getcnt(tmp,ds)-dp[i-1][ds];
		tmp/=10LL;
	}
	return ret;
}
unsigned long long solve1(unsigned long long n,unsigned long long k)
{
	char num[MAXD];
	sprintf(num,"%llu",k);
	int len=strlen(num);
	int sum=0;
	for(int i=0;i<len;i++)
		sum+=num[i]-'0';
	return getrank(n,k,sum);
}
unsigned long long solve2(unsigned long long n,unsigned long long k)
{
	char num[MAXD];
	unsigned long long ret=0LL,t,_k=k;
	int id=1,ds=0,j;
	while((t=getcnt(n,id))<_k)
	{
		id++;
		_k-=t;
	}
	while(1)
	{
		ret*=10;
		for(j=0;j<MAXN;j++)
			if(getrank(n,ret+j,id)>=k)
				break;
		ret+=j;
		ds=0;
		sprintf(num,"%llu",ret);
		for(int i=0;num[i];i++)
			ds+=num[i]-'0';
		if(getrank(n,ret,ds)==k)
			break;
		ret--;
	}
	return ret;
}
int main()
{
	init();
	unsigned long long n,k;
	while(1)
	{
		scanf("%llu%llu",&n,&k);
		if(!n&&!k)break;
		printf("%llu %llu\n",solve1(n,k),solve2(n,k));
	}
	return 0;
}
