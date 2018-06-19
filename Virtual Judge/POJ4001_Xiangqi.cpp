#include<cstdio>
#include<cstring>
const int MAXN=10,W=9,H=10;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
const int hdir[8][2]={{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2}};

struct piece
{
	char c[5];
	int x,y;
} p[MAXN];

int n,gx,gy;
bool check(int x,int y)
{return x>0&&y>0&&x<=H&&y<=W;}
bool check2(int x,int y)
{return x>0&&y>=4&&x<=3&&y<=6;}
bool danger[12][12];
bool has[12][12];

int main()
{
	for(;;)
	{
		scanf("%d%d%d",&n,&gx,&gy);
		if(n==0&&gx==0&&gy==0)
			break;
		memset(has,0,sizeof has);
		memset(danger,0,sizeof danger);
		memset(p,0,sizeof p);
		for(int i=1;i<=n;i++)
		{
			scanf("%s%d%d",p[i].c,&p[i].x,&p[i].y);
			has[p[i].x][p[i].y]=true;
		}
		
		bool error1=false;
		for(int i=1;i<=n;i++)
		{
			if(p[i].c[0]=='G')
			{
				for(int x=p[i].x-1;x>0;x--)
				{
					danger[x][p[i].y]=true;
					if(x==gx&&p[i].y==gy)
					{error1=true;break;}
					if(has[x][p[i].y])
						break;
				}
				if(error1)break;
			}
			else if(p[i].c[0]=='R')
			{
				for(int d=0;d<4;d++)
				{
					int x=p[i].x+dir[d][0],y=p[i].y+dir[d][1];
					while(check(x,y))
					{
						danger[x][y]=true;
						if(has[x][y])
							break;
						x+=dir[d][0],y+=dir[d][1];
					}
				}
			}
			else if(p[i].c[0]=='C')
			{
				for(int d=0;d<4;d++)
				{
					int x=p[i].x+dir[d][0],y=p[i].y+dir[d][1];
					bool flag=false;
					while(check(x,y)&&!flag)
					{
						if(has[x][y])
							flag=true;
						x+=dir[d][0],y+=dir[d][1];
					}
					while(check(x,y)&&flag)
					{
						danger[x][y]=true;
						if(has[x][y])
							break;
						x+=dir[d][0],y+=dir[d][1];
					}
				}
			}
			else if(p[i].c[0]=='H')
			{
				for(int d=0;d<8;d++)
				{
					int x=p[i].x+hdir[d][0],y=p[i].y+hdir[d][1];
					if(!check(x,y))
						continue;
					if(has[p[i].x+dir[d/2][0]][p[i].y+dir[d/2][1]])
						continue;
					danger[x][y]=true;
				}
			}
		}
		
		if(error1)
		{
			puts("NO");
			continue;
		}
		
		bool flag=true;
		for(int d=0;d<4&&flag;d++)
		{
			int x=gx+dir[d][0],y=gy+dir[d][1];
			if(!check2(x,y))
				continue;
			if(danger[x][y]==false)
				flag=false;
		}
		
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	
	return 0;
}
