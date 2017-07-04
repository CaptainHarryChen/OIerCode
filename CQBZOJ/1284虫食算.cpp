#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using std::swap;
#define MAXN 30
int N,finalR,ans[MAXN];
char eq[3][MAXN];
int A[MAXN][MAXN*2];
bool car[MAXN],vis[MAXN];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int lcm(int a,int b){return a/gcd(a,b)*b;}
inline void Init_Matrix()
{
	memset(A,0,sizeof A);
	for(int i=N-1;i>=0;i--)
	{
		A[i+1][eq[0][i]-'A'+1]++;
		A[i+1][eq[1][i]-'A'+1]++;
		A[i+1][eq[2][i]-'A'+1]--;
		A[i+1][N+i+1]=-N;
		A[i+1][N+i+2]=1;
		A[i+1][N*2+1]=0;
	}
}
inline void Gauss()
{
	int r,c,mxr,n=N,m=N*2+1,l,ta,tb;
	for(r=1,c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(abs(A[i][c])>abs(A[mxr][c]))
				mxr=i;
		if(A[mxr][c]==0)
		{r--;continue;}
		if(mxr!=r)swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&A[i][c])
			{
				l=lcm(abs(A[i][c]),abs(A[r][c]));
				ta=l/A[i][c];
				tb=l/A[r][c];
				for(int j=c;j<=m;j++)
					A[i][j]=A[i][j]*ta-A[r][j]*tb;
				if(i<c)
					A[i][i]*=ta;
			}
	}
	finalR=r-1;
}
inline bool Check()
{
	memset(vis,0,sizeof vis);
	memset(ans,0,sizeof ans);
	int sum;
	for(int i=N;i>0;i--)
	{
		sum=A[i][N*2+1];
		for(int j=N+1;j<=N*2;j++)
			sum-=A[i][j]*car[j-N];
		if(sum%A[i][i])return 0;
		ans[i]=sum/A[i][i];
		if(ans[i]<0||ans[i]>=N||vis[ans[i]])return 0;
		vis[ans[i]]=1;
	}
	for(int i=1;i<N;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[N]);
	return 1;
}
void Enum_carry(int id)
{
	if(id>N)
	{
		if(Check())
			exit(0);
		return;
	}
	car[id]=0;
	Enum_carry(id+1);
	car[id]=1;
	Enum_carry(id+1);
}
int main()
{
	scanf("%d%s%s%s",&N,eq[0],eq[1],eq[2]);
	Init_Matrix();
	Gauss();
	Enum_carry(2);
	printf("Error\n");
	return 0;
}
