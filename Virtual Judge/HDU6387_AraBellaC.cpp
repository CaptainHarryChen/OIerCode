#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXM=5005,MAXX=10005,MAXLOG=15;

int str[MAXX];
int ST1[3][MAXX][MAXLOG],ST2[3][MAXX][MAXLOG];
int lg[MAXX];

int main()
{
	for(int i=1,j=0;i<MAXX;i++)
	{
		if(i>=(1<<(j+1)))
			j++;
		lg[i]=j;
	}
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int m,x,maxX=0;
		char s[3];
		scanf("%d",&m);
		memset(str,-1,sizeof str);
		bool flag=true;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%s",&x,s);
			maxX=max(maxX,x);
			if(str[x]!=-1)
				flag=false;
			str[x]=s[0]-'A';
		}
		if(!flag)
		{
			puts("NO");
			continue;
		}
		for(int i=1;i<=maxX;i++)
			for(int c=0;c<3;c++)
			{
				if(c==str[i])
					ST1[c][i][0]=ST2[c][i][0]=i;
				else
				{
					ST1[c][i][0]=0x3FFFFFFF;
					ST2[c][i][0]=-0x3FFFFFFF;
				}
			}
		for(int j=1;(1<<j)<=maxX;j++)
			for(int i=1;i+(1<<j)-1<=maxX;i++)
				for(int c=0;c<3;c++)
				{
					ST1[c][i][j]=min(ST1[c][i][j-1],ST1[c][i+(1<<(j-1))][j-1]);
					ST2[c][i][j]=max(ST2[c][i][j-1],ST2[c][i+(1<<(j-1))][j-1]);
				}
		int ansa=-1,ansb=-1,ansc=-1;
		for(int len=3;len<=maxX;len++)
		{
			int a2=1,b1=len-1,b2=2,c1=len;
			for(int i=1;i<=maxX;i+=len)
			{
				int l=i,r=min(maxX,i+len-1),t=lg[r-l+1];
				a2=max(a2,max(ST2[0][l][t],ST2[0][r-(1<<t)+1][t])-l+1);
				b1=min(b1,min(ST1[1][l][t],ST1[1][r-(1<<t)+1][t])-l+1);
				b2=max(b2,max(ST2[1][l][t],ST2[1][r-(1<<t)+1][t])-l+1);
				c1=min(c1,min(ST1[2][l][t],ST1[2][r-(1<<t)+1][t])-l+1);
			}
			if(a2<b1&&b2<c1)
			{
				int a=a2,b=b2-a,c=len-a-b;
				if(ansa==-1||a<ansa||(a==ansa&&b<ansb)||(a==ansa&&b==ansb&&c<ansc))
					ansa=a,ansb=b,ansc=c;
			}
		}
		if(ansa==-1)
			puts("NO");
		else
			printf("%d %d %d\n",ansa,ansb,ansc);
	}
	
	return 0;
}
