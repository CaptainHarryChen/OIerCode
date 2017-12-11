#include<cstdio>
const int MAXN=10000005;
int inv[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=(int)((1LL*(1LL*(n-n/i)%n)*inv[n%i])%n);
	for(int i=(n-100<=0?1:n-100);i<n;i++)
		printf("%d\n",inv[i]);
	return 0;
}
