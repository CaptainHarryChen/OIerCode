#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2147483647
#define MAXN 1000100
using namespace std;
int p,q,n,m,ca[MAXN],cb[MAXN],A,B,C,D,E,F,a1,a2,b1,b2;
long long cnt;
int main()
{
	scanf("%d%d",&p,&q);
	scanf("%d%d%d%d%d%d",&n,&a1,&a2,&A,&B,&C);
	scanf("%d%d%d%d%d%d",&m,&b1,&b2,&D,&E,&F);
	a1%=p;a2%=p;A%=p;B%=p;C%=p;
	ca[a1]++;ca[a2]++;
	b1%=p-1;b2%=p-1;D%=p-1;E%=p-1;F%=p-1;
	cb[b1]++;cb[b2]++;
	int t;
	for(int i=3;i<=n;i++)
	{
		t=(a2*A)%p-(a1*B)%p-C;
		t%=p;
		if(t<0)t+=p;
		ca[t]++;
		a1=a2;a2=t;
	}
	for(int i=3;i<=m;i++)
	{
		t=(b2*D)%(p-1)+(b1*E)%(p-1)+F;
		t%=(p-1);
		cb[t]++;
		b1=b2;b2=t;
	}
	cnt=(long long)ca[0]*m;
	for(int i=1;i<p;i++)
	{
		if(ca[i]==0)continue;
		t=1;
		for(int j=0;j<p-1;j++)
		{
			if(t<=q)
				cnt+=(long long)ca[i]*cb[j];
			t=t*i%p;
		}
	}
	printf("%I64d\n",cnt);
	return 0;
}
