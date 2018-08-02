#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=10005,MAXK=28,MAXLOG=32,MAXS=120005;

struct Edge
{
	int v,w;
	Edge(int v,int w):v(v),w(w){}
};

int N,M,K;
int nxt[MAXN][MAXK][MAXLOG],val[MAXN][MAXK][MAXLOG];
char str[MAXS];

int main()
{
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=K;j++)
		{
			int A,B;
			scanf("%d%d",&A,&B);
			nxt[i][j][0]=A;
			val[i][j][0]=B;
		}
	scanf("%s%d",str,&M);
	
	for(int j=1;j<MAXLOG;j++)
		for(int i=1;i<=N;i++)
			for(int k=1;k<=K;k++)
			{
				nxt[i][k][j]=nxt[nxt[i][k][j-1]][k][j-1];
				val[i][k][j]=(val[i][k][j-1]+val[nxt[i][k][j-1]][k][j-1])%M;
			}
	
	int ans=0,now=1,S;
	for(int i=0,j;str[i];)
	{
		if(str[i]=='[')
		{
			S=0;
			for(j=i+1;str[j]>='0'&&str[j]<='9';j++)
				S=S*10+str[j]-'0';
			i=j+2;
		}
		else
			S=1,j=i,i++;
		for(int l=MAXLOG-1;l>=0;l--)
			if((1LL<<l)<=S)
			{
				ans=(ans+val[now][str[j]-'A'+1][l])%M;
				now=nxt[now][str[j]-'A'+1][l];
				S-=(1<<l);
			}
	}
	printf("%d\n",ans);
	
	return 0;
}
