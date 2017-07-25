#include<cstdio>
#include<cstring>
const int MAXN=1005;
int N;
class BIT
{
	int sum[MAXN][MAXN];
public:
	void clear()
	{
		memset(sum,0,sizeof sum);
	}
	void add(int x,int y,int val)
	{
		x++;y++;
		for(int i=x;i<=N;i+=i&(-i))
			for(int j=y;j<=N;j+=j&(-j))
				sum[i][j]+=val;
	}
	int get(int x,int y)
	{
		x++;y++;
		int ret=0;
		for(int i=x;i>0;i-=i&(-i))
			for(int j=y;j>0;j-=j&(-j))
				ret+=sum[i][j];
		return ret;
	}
};
BIT opcnt;
int main()
{
	int X,T,x,y,x1,y1,x2,y2,ans;
	char op[5];
	scanf("%d",&X);
	while(X--)
	{
		scanf("%d%d",&N,&T);
		opcnt.clear();
		for(int i=1;i<=T;i++)
		{
			scanf("%s",op);
			if(op[0]=='C')
			{
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				opcnt.add(x2,y2,1);
				opcnt.add(x1-1,y2,1);
				opcnt.add(x2,y1-1,1);
				opcnt.add(x1-1,y1-1,1);
			}
			else
			{
				scanf("%d%d",&x,&y);
				ans=opcnt.get(x-1,y-1);
				printf("%d\n",ans%2);
			}
		}
		puts("");
	}
	return 0;
}
