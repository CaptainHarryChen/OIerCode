#include<cstdio>
int solve(long long K,long long M,long long X)
{
	//m0M0
	if(X<=K*8LL&&X!=K*8LL-1LL)
		return 1;
	//m1M0
	long long tX=X-M;
	if(tX>=2&&tX<=K*5LL&&tX!=K*5LL-1LL)
		return 1;
	//m2M0<=m0M1
	//m3M0 imposible
	//m0M1
	tX=X-2LL*M;
	if(tX>=0&&((tX%3LL==0&&tX<=K*6LL)||(tX<=K*5LL&&tX!=K*5LL-1LL)))
		return 1;
	//m1M1
	tX-=M;
	if(tX>=0&&(tX<=K||(tX<=2LL*K&&tX%2LL==0)||(tX<=3LL*K&&tX%3LL==0)))
		return 1;
	//m2M1;
	if(tX==M)
		return 1;
	//m0M2
	tX=X-4LL*M;
	if(tX>=0&&(tX<=K||(tX<=2LL*K&&tX%2LL==0)||(tX<=3LL*K&&tX%3LL==0)))
		return 1;
	//m1M2
	if(tX==M)
		return 1;
	//M3
	if(tX==M*6LL)
		return 1;
	//no solution
	return 0;
}
int main()
{
	long long A[5],B[5],C[5],D[5],X[5];
	int T,ans=0;
	scanf("%d",&T);
	for(int j=1;j<=3;j++)
		scanf("%lld%lld%lld%lld%lld",&A[j],&B[j],&C[j],&D[j],&X[j]);
	for(int i=1;i<=T;i++)
	{
		ans+=solve(X[1],X[2],X[3]);
		for(int j=1;j<=3;j++)
			X[j]=((X[j]*X[j]%D[j]*A[j]%D[j]
			+X[j]*B[j]%D[j])%D[j]+C[j])%D[j]+20LL;
	}
	printf("%d\n",ans);
	return 0;
}
