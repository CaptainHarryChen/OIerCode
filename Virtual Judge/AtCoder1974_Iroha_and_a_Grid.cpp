#include<cstdio>
#include<cstring>
const int MAXN=100005,MOD=1000000007;

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}
int Inv(int a)
{return PowMod(a,MOD-2);}

int tmp1[MAXN],tmp2[MAXN];

int main()
{
	int H,W,A,B;
	scanf("%d%d%d%d",&H,&W,&A,&B);
	
	tmp1[1]=1;
	for(int i=2;i<=H-A;i++)
		tmp1[i]=1LL*tmp1[i-1]*(B-2+i)%MOD*Inv(i-1)%MOD;
	
	tmp2[1]=1;
	for(int i=2;i<=H;i++)
		tmp2[i]=1LL*tmp2[i-1]*(W-B-2+i)%MOD*Inv(i-1)%MOD;
		
	int ans=0;
	for(int i=1;i<=H-A;i++)
		ans=(ans+1LL*tmp1[i]*tmp2[H-i+1]%MOD)%MOD;
	
	printf("%d\n",ans);
	
	return 0;
}
