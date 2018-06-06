#include<cstdio>
#include<queue>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double EPS=1e-8;
const int MAXN=205;
typedef double Matrix[MAXN][MAXN];

int dcmp(double a,double b)
{
	if(fabs(a-b)<EPS)return 0;
	if(a<b)return -1;
	return 1;
}

int T,N,M,ed,st,D,n;
int P[MAXN];
Matrix eq;

bool BFS()
{
	static bool vis[MAXN];
	bool flag=false;
	queue<int> Q;
	memset(vis,0,sizeof vis);
	memset(eq,0,sizeof eq);
	Q.push(st);
	vis[st]=true;
	while(!Q.empty())
	{
		int t=Q.front();Q.pop();
		eq[t][t]=1;
		if(t==ed||t==n-ed)
		{flag=true;continue;}
		for(int j=1;j<=M;j++)
			if(P[j]!=0)
			{
				eq[t][(t+j)%n]-=P[j]/100.0;
				eq[t][n]+=j*P[j]/100.0;
				if(!vis[(t+j)%n])
				{
					Q.push((t+j)%n);
					vis[(t+j)%n]=true;
				}
			}
	}
	return flag;
}

void Gauss(int row,int col)
{
	int r=0,c=0;
	for(;r<row&&c<=col;r++,c++)
	{
		int mxr=r;
		for(int i=r+1;i<row;i++)
			if(dcmp(fabs(eq[mxr][c]),fabs(eq[i][c]))==-1)
				mxr=i;
		if(dcmp(eq[mxr][c],0)==0)
		{r--;continue;}
		if(mxr!=r)
			for(int j=0;j<=col;j++)
				swap(eq[mxr][j],eq[r][j]);
		for(int i=0;i<row;i++)
			if(i!=r)
				for(int j=col;j>=c;j--)
					eq[i][j]=eq[i][j]-eq[r][j]*eq[i][c]/eq[r][c];
	}
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d%d",&N,&M,&ed,&st,&D);
		for(int i=1;i<=M;i++)
			scanf("%d",&P[i]);
		if(st==ed)
		{
			puts("0.00");
			continue;
		}
		n=N*2-2;//012...(n-1)n(n-1)...1
		if(D==1)
			st=n-st;
		if(!BFS())
		{
			puts("Impossible !");
			continue;
		}
		Gauss(n,n);
		double ans=0;
		for(int i=0;i<n;i++)
			if(dcmp(eq[i][st],0)!=0)
			{ans=eq[i][n]/eq[i][st];break;}
		if(dcmp(ans,0)!=1)
			puts("Impossible !");
		else
			printf("%.2lf\n",ans);
	}
	
	return 0;
}
