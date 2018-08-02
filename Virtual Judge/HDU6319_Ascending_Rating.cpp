#include<cstdio>
const int MAXN=10000005;

int n,m;
int a[MAXN];
int que1[MAXN],hd1,tl1;
int que2[MAXN],hd2,tl2;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int k,p,q,r,MOD;
		scanf("%d%d%d%d%d%d%d",&n,&m,&k,&p,&q,&r,&MOD);
		for(int i=1;i<=k;i++)
			scanf("%d",&a[i]);
		for(int i=k+1;i<=n;i++)
			a[i]=(1LL*p*a[i-1]+1LL*q*i+r)%MOD;
		
		long long A=0,B=0;
		
		hd1=tl1=0;
		for(int i=1;i<=n;i++)
		{
			while(hd1<tl1&&a[que1[tl1-1]]<=a[i])
				tl1--;
			que1[tl1++]=i;
			if(i>=m)
			{
				while(hd1<tl1&&que1[hd1]<i-m+1)
					hd1++;
				A+=(a[que1[hd1]]^(i-m+1));
			}
		}
		
		hd2=tl2=0;
		for(int i=n;i>=1;i--)
		{
			while(hd2<tl2&&a[que2[tl2-1]]<=a[i])
				tl2--;
			que2[tl2++]=i;
			if(i<=n-m+1)
			{
				while(hd2<tl2&&que2[hd2]>i+m-1)
					hd2++;
				B+=((tl2-hd2)^i);
			}
		}
		printf("%I64d %I64d\n",A,B);
	}
	
	return 0;
}
