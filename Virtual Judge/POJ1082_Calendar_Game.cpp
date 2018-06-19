#include<cstdio>
const int Month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Date
{
	int y,m,d;
	Date(int a,int b,int c){y=a;m=b;d=c;}
	bool leap(){return y%4==0&&(y%100!=0||y==100);}
	void GoPrev()
	{
		d--;
		if(d==0)
		{
			m--,d=Month[m];
			if(m==2&&leap())
				d++;
		}
		if(m==0)
			y--,m=12,d=31;
	}
	Date Next()
	{
		Date ret=*this;
		ret.d++;
		if(ret.d>(Month[m]+(m==2&&leap())))
			ret.m++,ret.d=1;
		if(ret.m>12)
			ret.y++,ret.m=1,ret.d=1;
		return ret;
	}
	bool HaveNextMonth()
	{return d<=(Month[m%12+1]+(m==1&&leap()));}
	Date NextMonth()
	{
		Date ret=*this;
		ret.m++;
		if(ret.m>12)
			ret.y++,ret.m=1;
		return ret;
	}
	bool operator < (const Date &t)const
	{return y<t.y||(y==t.y&&(m<t.m||(m==t.m&&d<t.d)));}
};

bool dp[200][15][35];

int main()
{
	Date x(101,11,4);
	do
	{
		x.GoPrev();
		Date y=x.Next();
		if(dp[y.y][y.m][y.d]==false)
			dp[x.y][x.m][x.d]=true;
		if(!x.HaveNextMonth())
			continue;
		y=x.NextMonth();
		if(Date(101,11,4)<y)
			continue;
		if(dp[y.y][y.m][y.d]==false)
			dp[x.y][x.m][x.d]=true;
	}while(Date(0,1,1)<x);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(dp[a-1900][b][c])
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
