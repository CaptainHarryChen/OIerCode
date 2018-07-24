#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MAXLOG=20;

int n,m,Type;
int A[MAXN];
long long l[MAXN],r[MAXN];
int mx[MAXN][MAXLOG],mxid[MAXN][MAXLOG];
int stk[MAXN],top;

int getRMQ(int L,int R)
{
	int j=MAXLOG-1;
	while(L+(1<<j)-1>R)
		j--;
	if(mx[L][j]>mx[R-(1<<j)+1][j])
		return mxid[L][j];
	return mxid[R-(1<<j)+1][j];
}

int main()
{
	scanf("%d%d%d",&n,&m,&Type);
	for(int i=1;i<=n;i++)
		scanf("%d",A+i);
	top=0;
	l[1]=0;stk[++top]=A[1];
	for(int i=2;i<=n;i++)
	{
		while(top&&stk[top]<A[i])
			top--,l[i]++;
		if(top)
			l[i]++;
		while(top&&stk[top]<=A[i])
			top--;
		stk[++top]=A[i];
	}
	top=0;
	r[n]=0;stk[++top]=A[n];
	for(int i=n-1;i>=1;i--)
	{
		while(top&&stk[top]<A[i])
			top--,r[i]++;
		if(top)
			r[i]++;
		while(top&&stk[top]<=A[i])
			top--;
		stk[++top]=A[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		l[i]+=l[i-1],r[i]+=r[i-1];
		mx[i][0]=A[i],mxid[i][0]=i;
	}
	for(int j=1;(1<<j)<n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			if(mx[i][j-1]>=mx[i+(1<<(j-1))][j-1])
				mx[i][j]=mx[i][j-1],mxid[i][j]=mxid[i][j-1];
			else
				mx[i][j]=mx[i+(1<<(j-1))][j-1],mxid[i][j]=mxid[i+(1<<(j-1))][j-1];
		}
		
	long long last=0;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(Type)
		{
			a=(a+last-1)%n+1;
			b=(b+last-1)%n+1;
		}
		if(a>b)
			swap(a,b);
		int mid=getRMQ(a,b);
		long long res=(r[mid-1]-r[a-1])+(l[b]-l[mid]);
		last=res;
		printf("%lld\n",res);
	}
	
	return 0;
}
