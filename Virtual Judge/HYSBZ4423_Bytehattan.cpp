#include<cstdio>
#include<cstring>
const int MAXN=1505;

int dsu[MAXN*MAXN];
int Root(int x)
{
	if(dsu[x]==-1)
		return x;
	return dsu[x]=Root(dsu[x]);
}

int main()
{
	memset(dsu,-1,sizeof dsu);
	int n,k;
	scanf("%d%d",&n,&k);
	int la=0;
	int u[2],v[2];
	char d[2][3];
	while(k--)
	{
		scanf("%d%d%s%d%d%s",&u[0],&v[0],d[0],&u[1],&v[1],d[1]);
		int a,b,x,y;
		if(d[la][0]=='E')
			x=u[la],y=v[la]-1;
		else
			x=u[la]-1,y=v[la];
			
		if(x<=0||y<=0||x>n||y>n)a=0;
		else a=(x-1)*(n-1)+y;
			
		if(u[la]<=0||v[la]<=0||u[la]>=n||v[la]>=n)b=0;
		else b=(u[la]-1)*(n-1)+v[la];

		int r1=Root(a),r2=Root(b);
		if(r1==r2)
			la=1;
		else
		{
			la=0;
			dsu[r1]=r2;
		}
		if(la)
			puts("NIE");
		else
			puts("TAK");
	}
	return 0;
}
