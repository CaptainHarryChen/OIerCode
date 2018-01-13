#include<cstdio>
#include<cstdlib>

int g,rings,runes;
int rid[105][5];

bool Error1()
{
	for(int i=1;i<=runes;i++)
		for(int j=1;j<=3;j++)
			if(rid[i][j]==0)
				return true;
	return false;
}
bool Error2()
{
	for(int i=1;i<=runes;i++)
		for(int j=1;j<=3;j++)
			if(rid[i][j]<-rings||rid[i][j]>rings)
				return true;
	return false;
}
bool Error3()
{
	for(int i=1;i<=runes;i++)
	{
		int a=abs(rid[i][1]),b=abs(rid[i][2]),c=abs(rid[i][3]);
		if(a==b||b==c||a==c)
			return true;
	}
	return false;
}
bool check(int s)
{
	for(int i=1;i<=runes;i++)
	{
		bool flag=false;
		for(int j=1,r;j<=3;j++)
			if(rid[i][j]<0)
			{
				r=-rid[i][j];
				if((s&(1<<(r-1)))==0)
				{flag=true;break;}
			}
			else
			{
				r=rid[i][j];
				if(s&(1<<(r-1)))
				{flag=true;break;}
			}
		if(!flag)return false;
	}
	return true;
}

int main()
{
	scanf("%d",&g);
	while(g--)
	{
		scanf("%d%d",&rings,&runes);
		for(int i=1;i<=runes;i++)
			for(int j=1;j<=4;j++)
				scanf("%d",&rid[i][j]);
		if(Error1())
		{
			puts("INVALID: NULL RING");
			continue;
		}
		if(Error2())
		{
			puts("INVALID: RING MISSING");
			continue;
		}
		if(Error3())
		{
			puts("INVALID: RUNE CONTAINS A REPEATED RING");
			continue;
		}
		bool flag=false;
		for(int s=0;s<(1<<rings);s++)
			if(check(s))
			{
				flag=true;
				break;
			}
		if(flag)
			puts("RUNES SATISFIED!");
		else
			puts("RUNES UNSATISFIABLE! TRY ANOTHER GATE!");
	}
	return 0;
}
