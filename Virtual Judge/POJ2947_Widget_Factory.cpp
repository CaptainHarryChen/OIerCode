#include<cstdio>
#include<cstring>
#include<algorithm>
using std::swap;
#define MAXN 305
const int weekdays=7;
const char weekday[7][5]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
int getDay(char *s)
{
	int i;
	for(i=0;i<7&&strcmp(s,weekday[i])!=0;i++);
	return i+1;
}
int n,m;
int A[MAXN][MAXN],finalR;
int gcd(int a,int b)
{
	int t;
	while(b)
	{
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}
int lcm(int a,int b)
{return a/gcd(a,b)*b;}
int pow_mod(int a,int b,int p)
{
	int ret=1;
	for(;b;b>>=1,a=(a*a)%p)
		if(b&1)
			ret=(ret*a)%p;
	return ret;
}
int inv(int a,int p)
{return pow_mod(a,p-2,p);}
void Init()
{
	memset(A,0,sizeof A);
	int k,i,j,id;
	char s[5],e[5];
	for(i=1;i<=m;i++)
	{
		scanf("%d%s%s",&k,s,e);
		A[i][n+1]=(getDay(e)-getDay(s)+1+weekdays)%weekdays;
		for(j=1;j<=k;j++)
		{
			scanf("%d",&id);
			A[i][id]++;
			A[i][id]%=weekdays;
		}
	}
}
void Gauss()
{
	int r,c,t,i,j,l,ta,tb;
	for(r=1,c=1;r<=m&&c<=n;r++,c++)
	{
		for(t=r;!A[t][c]&&t<=m;t++);
		if(!A[t][c]){r--;continue;}
		if(t!=r)swap(A[t],A[r]);
		for(i=1;i<=m;i++)
			if(i!=r&&A[i][c])
			{
				l=lcm(A[i][c],A[r][c]);
				ta=l/A[i][c];
				tb=l/A[r][c];
				for(j=1;j<=n+1;j++)
					A[i][j]=((A[i][j]*ta-A[r][j]*tb)%weekdays+weekdays)%weekdays;
			}
	}
	finalR=r-1;
}
void Check()
{
	int i;
	for(i=finalR+1;i<=m;i++)
		if(A[i][n+1])
		{
			printf("Inconsistent data.\n");
			return;
		}
	if(finalR<n)
	{
		printf("Multiple solutions.\n");
		return;
	}
	int ans;
	for(int i=1;i<n;i++)
	{
		ans=A[i][n+1]*inv(A[i][i],weekdays)%weekdays;
		if(ans<3)ans+=weekdays;
		printf("%d ",ans);
	}
	ans=A[n][n+1]*inv(A[n][n],weekdays)%weekdays;
	if(ans<3)ans+=weekdays;
	printf("%d\n",ans);
}
int main()
{
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(!n&&!m)break;
		Init();
		Gauss();
		Check();
	}
	return 0;
}
