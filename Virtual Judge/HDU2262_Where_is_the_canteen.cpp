#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const double EPS=1e-8;
const int MAXN=17,MAXE=230;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
typedef double Matrix[MAXE][MAXE];
int dcmp(double a,double b)
{
	if(fabs(a-b)<EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}
	
int n,m;

bool check(int i,int j)
{return i>0&&j>0&&i<=n&&j<=m;}
int encode(int i,int j)
{return (i-1)*m+j;}
void decode(int c,int &i,int &j)
{i=(c-1)/m+1;j=(c-1)%m+1;}

char camp[MAXN][MAXN];
bool vis[MAXN][MAXN];
int stx,sty;
Matrix eq;
//dp[i][j]=(dp[i-1][j]+dp[i][j+1]+dp[i+1][j]+dp[i][j-1])/4+1;
void Gauss(int n,int m)
{
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m+1;j++)
			printf("%4.1lf ",eq[i][j]);
		puts("");
	}
	puts("---");*/
	for(int r=1,c=1;r<=n&&c<=m+1;r++,c++)
	{
		int mxr=r;
		for(int i=r+1;i<=n;i++)
			if(dcmp(fabs(eq[mxr][c]),fabs(eq[i][c]))==-1)
				mxr=i;
		if(dcmp(eq[mxr][c],0)==0)
		{
			r--;
			continue;
		}
		if(mxr!=r)
			for(int j=1;j<=m+1;j++)
				swap(eq[r][j],eq[mxr][j]);
		for(int i=1;i<=n;i++)
			if(i!=r)
			{
				double k=eq[i][c]/eq[r][c];
				for(int j=c;j<=m+1;j++)
					eq[i][j]=eq[i][j]-eq[r][j]*k;
			}
		/*for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m+1;j++)
				printf("%4.1lf ",eq[i][j]);
			puts("");
		}
		puts("---");*/
	}
}

void Init()
{
	memset(eq,0,sizeof eq);
	memset(camp,0,sizeof camp);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",camp[i]+1);
		for(int j=1;j<=m;j++)
			if(camp[i][j]=='@')
				stx=i,sty=j;
	}
}

bool bfs()
{
	bool flag=false;
	memset(vis,0,sizeof vis);
	queue<int> Q;
	Q.push(encode(stx,sty));
	vis[stx][sty]=true;
	while(!Q.empty())
	{
		int k=Q.front();
		Q.pop();
		int i,j;
		decode(k,i,j);
		int cnt=0;
		for(int d=0;d<4;d++)
		{
			int ti=i+dir[d][0],tj=j+dir[d][1];
			if(!check(ti,tj)||camp[ti][tj]=='#')
				continue;
			cnt++;
		}
		eq[k][k]=1;
		if(camp[i][j]=='$')
		{
			flag=true;
			continue;
		}
		for(int d=0;d<4;d++)
		{
			int ti=i+dir[d][0],tj=j+dir[d][1];
			if(!check(ti,tj)||camp[ti][tj]=='#')
				continue;
			eq[k][encode(ti,tj)]=-1.0/cnt;
			if(!vis[ti][tj])
			{
				vis[ti][tj]=true;
				Q.push(encode(ti,tj));
			}
		}
		eq[k][n*m+1]=1;
	}
	return flag;
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		Init();
		if(!bfs())
			puts("-1");
		else
		{
			Gauss(n*m,n*m);
			int s=encode(stx,sty);
			double ans;
			for(int i=1;i<=n*m;i++)
				if(dcmp(eq[i][s],0.0)!=0)
					ans=eq[i][n*m+1]/eq[i][s];
			printf("%.6lf\n",ans);
		}
	}
	
	return 0;
}
