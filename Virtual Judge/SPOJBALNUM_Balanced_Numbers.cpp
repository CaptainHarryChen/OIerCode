#include<cstdio>
#include<cstring>
const int MAXN=20,MAXS=59049,MAXD=10;

void decode(int c,int res[])
{
	for(int i=0;i<MAXD;i++,c/=3)
		res[i]=c%3;
}
int encode(int c[])
{
	int res=0;
	for(int i=0,dig=1;i<MAXD;i++,dig*=3)
		res+=c[i]*dig;
	return res;
}

long long dp[MAXN][MAXS+10];

void DP()
{
	memset(dp,0,sizeof dp);
	dp[0][0]=1;
	for(int i=1;i<MAXN;i++)
		for(int j=0;j<MAXS;j++)
		{
			int st[MAXD];
			decode(j,st);
			for(int d=0;d<MAXD;d++)
				if(st[d]==1)
				{
					st[d]=0;dp[i][j]+=dp[i-1][encode(st)];
					st[d]=2;dp[i][j]+=dp[i-1][encode(st)];
					st[d]=1;
				}
				else if(st[d]==2)
				{
					st[d]=1;dp[i][j]+=dp[i-1][encode(st)];
					st[d]=2;
				}
		}
}

bool check(const int st1[],const int st2[])
{
	for(int i=0,x;i<MAXD;i++)
	{
		if(st1[i]==0)x=st2[i];
		else if(st2[i]==0)x=st1[i];
		else x=((st1[i]-1)^(st2[i]-1)),x=x==0?2:1;
		if((x==1&&i%2==1)||(x==2&&i%2==0))
			return false;
	}
	return true;
}

void Update(long long &res,int i,const int st[],int tst[],int d=0)
{
	if(d>=MAXD)
	{
		int j=encode(tst);
		res+=dp[i][j];
		return;
	}
	if(st[d]==0)
	{
		tst[d]=0;Update(res,i,st,tst,d+1);
		tst[d]=d%2==0?1:2;Update(res,i,st,tst,d+1);
	}
	else
	{
		if((st[d]==1&&d%2==0)||(st[d]==2&&d%2==1))
		{
			tst[d]=0;Update(res,i,st,tst,d+1);
			tst[d]=2;Update(res,i,st,tst,d+1);
		}
		else
			tst[d]=1,Update(res,i,st,tst,d+1);
	}
}

long long solve(long long N)
{
	char dig[MAXN];
	int st[MAXD]={0},tst[MAXD];
	
	sprintf(dig+1,"%lld",N);
	int len=strlen(dig+1);
	long long ret=0;
	
	for(int i=1;i<len;i++)
		for(int d=1;d<MAXD;d++)
		{
			st[d]=1;
			Update(ret,i-1,st,tst);
			st[d]=0;
		}
	
	for(int i=len;i>0;i--)
	{
		for(int d=i==len?1:0;d<dig[len-i+1]-'0';d++)
		{
			int temp=st[d];
			st[d]=st[d]==2?1:st[d]+1;
			Update(ret,i-1,st,tst);
			st[d]=temp;
		}
		int nd=dig[len-i+1]-'0';
		st[nd]=st[nd]==2?1:st[nd]+1;
	}
	return ret;
}

int main()
{
	DP();
	
	int T;
	long long A,B;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&A,&B);
		printf("%lld\n",solve(B+1)-solve(A));
	}
	
	return 0;
}
