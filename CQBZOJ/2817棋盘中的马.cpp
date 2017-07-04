#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int n,m,dd[8][2]={{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
bool f[1005][1005];
struct house
{
	int x,y,id;
	house(){}
	house(int a,int b,int i)
	{x=a;y=b;id=i;}
};
bool f_(int x,int y)
{
	if(x>0&&y>0&&x<=n&&y<=m)return 1;
	return 0;
}
int bfs(int x1,int y1,int x2,int y2)
{
	house a=house(x1,y1,0);
	f[x1][y1]=1;
	queue<house>q;
	q.push(a);
	while(!q.empty())
	{
		house tt=q.front();
		q.pop();
		tt.id++;
		for(int i=0;i<8;i++)
		{
			house t=house(tt.x,tt.y,tt.id);
			t.x+=dd[i][0];
			t.y+=dd[i][1];
			if(f_(t.x,t.y)&&f[t.x][t.y]!=1)
			{
				if(t.x==x2&&t.y==y2)
					return t.id;
				f[t.x][t.y]=1;
				q.push(t);
			}
		}
	}
	return -1;
}
int main()
{
	int x1,x2,y1,y2;
	cin>>n>>m>>x1>>y1>>x2>>y2;
	cout<<bfs(x1,y1,x2,y2)<<endl;
	return 0;
}
