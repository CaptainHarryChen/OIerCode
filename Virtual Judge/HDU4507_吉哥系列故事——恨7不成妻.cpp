#include<cstdio>
#include<cstring>
const int MAXD=20,MAXN=10,MAXM=7,MOD=1000000007;
typedef long long DP[MAXD][MAXN][MAXM][MAXM];
DP A,B,C;//A:平方和；B:普通的和；C:数量
void init()
{
	C[0][0][0][0]=1LL;
	int pow10m7=1;
	long long pow10=1LL,a,b,c;
	for(int i=1;i<MAXD;i++)
	{
		for(int j=0;j<MAXN;j++)
		{
			if(j==7)continue;
			for(int r1=0;r1<MAXM;r1++)
				for(int r2=0;r2<MAXM;r2++)
					for(int k=0;k<MAXN;k++)
					{
						if(k==7)continue;
						int tr1=(r1-j%MAXM+MAXM)%MAXM;
						int tr2=(r2-(j*pow10m7)%MAXM+MAXM)%MAXM;
						a=A[i-1][k][tr1][tr2];
						b=B[i-1][k][tr1][tr2];
						c=C[i-1][k][tr1][tr2];
						A[i][j][r1][r2]+=a
						+((2LL*j*pow10)%MOD*b)%MOD
						+((((pow10*pow10)%MOD*j)%MOD*j)%MOD*c)%MOD;
						B[i][j][r1][r2]+=b
						+((j*pow10)%MOD*c)%MOD;
						C[i][j][r1][r2]+=c;
						A[i][j][r1][r2]%=MOD;
						B[i][j][r1][r2]%=MOD;
						C[i][j][r1][r2]%=MOD;
					}
		}
		pow10=(pow10*10LL)%MOD;
		pow10m7=(pow10m7*10)%MAXM;
	}
}
long long solve(long long N)
{
	long long ret=0LL,pow10=1LL,tmp=0LL;
	int tr1=0,tr2=0,pow10m7=1;
	char str[MAXD];
	sprintf(str,"%I64d",N);
	int len=strlen(str);
	for(int l=1;l<len;l++)
	{
		pow10=(pow10*10LL)%MOD;
		pow10m7=(pow10m7*10)%MAXM;
	}
	for(int i=len;i>0;i--)
	{
		for(int j=0;j<str[len-i]-'0';j++)
		{
			if(j==7)continue;
			for(int r1=0;r1<MAXM;r1++)
			{
				if(r1==tr1)continue;
				for(int r2=0;r2<MAXM;r2++)
				{
					if(r2==tr2)continue;
					ret+=A[i][j][r1][r2]
					+((2LL*tmp)%MOD*B[i][j][r1][r2])%MOD
					+(((tmp%MOD)*tmp)%MOD*C[i][j][r1][r2])%MOD;
					ret%=MOD;
				}
			}
		}
		if(str[len-i]=='7')break;
		tmp=(tmp+((str[len-i]-'0')*pow10)%MOD)%MOD;
		tr1=(tr1+MAXM-(str[len-i]-'0')%MAXM)%MAXM;
		tr2=(tr2+MAXM-((str[len-i]-'0')*pow10m7)%MAXM)%MAXM;
		pow10=(pow10*700000005LL)%MOD;
		pow10m7=(pow10m7*5)%MOD;
	}
	return ret;
}
int main()
{
	init();
	int T;
	long long L,R;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%I64d%I64d",&L,&R);
		printf("%I64d\n",(solve(R+1)-solve(L)+MOD)%MOD);
	}
	return 0;
}
