#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN=1005,MAXL=1000005;
const int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
typedef pair<int,int>Point;
typedef pair<Point,Point>Matrix;
int W,H;
int disx[MAXL],disy[MAXL];
int sortx[MAXN*2],sorty[MAXN*2],maxx,maxy;
Matrix mat[MAXN];
bool hided[MAXN][MAXN];
void mark(const Point &s,int W,int H)
{
	queue<Point> Q;
	hided[s.first][s.second]=1;
	Q.push(s);
	while(!Q.empty())
	{
		Point t=Q.front(),tt;
		Q.pop();
		for(int i=0;i<4;i++)
		{
			tt=Point(t.first+dir[i][0],t.second+dir[i][1]);
			if(tt.first<0||tt.first>=W||tt.second<0||tt.second>=H||hided[tt.first][tt.second])
				continue;
			hided[tt.first][tt.second]=1;
			Q.push(tt);
		}
	}
}
int main()
{
	int n;
	while(1)
	{
		scanf("%d%d",&W,&H);
		if(!W&&!H)
			break;
		sortx[1]=W;
		sorty[1]=H;
		scanf("%d",&n);
		for(int i=1,x1,y1,x2,y2;i<=n;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			sortx[i*2]=x1;sortx[i*2+1]=x2;
			sorty[i*2]=y1;sorty[i*2+1]=y2;
			mat[i]=Matrix(Point(x1,y1),Point(x2,y2));
		}
		sort(sortx+1,sortx+n*2+2);
		sort(sorty+1,sorty+n*2+2);
		maxx=unique(sortx,sortx+n*2+2)-sortx;
		maxy=unique(sorty,sorty+n*2+2)-sorty;
		fill(disx,disx+MAXL,-1);
		fill(disy,disy+MAXL,-1);
		for(int i=0;i<maxx;i++)
			disx[sortx[i]]=i;
		for(int i=0;i<maxy;i++)
			disy[sorty[i]]=i;
		memset(hided,0,sizeof hided);
		for(int i=1;i<=n;i++)
			for(int x=disx[mat[i].first.first];x<disx[mat[i].second.first];x++)
				for(int y=disy[mat[i].first.second];y<disy[mat[i].second.second];y++)
					hided[x][y]=1;
		int ans=0;
		for(int x=0;x<disx[W];x++)
			for(int y=0;y<disy[H];y++)
				if(!hided[x][y])
				{
					ans++;
					mark(Point(x,y),disx[W],disy[H]);
				}
		printf("%d\n",ans);
	}
	return 0;
}
