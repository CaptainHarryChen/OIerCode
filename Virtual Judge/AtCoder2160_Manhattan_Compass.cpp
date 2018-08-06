#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
using namespace std;
const int MAXN=100005;

struct Point
{
	int x,y,id;
	Point(int _x=0,int _y=0,int _id=0)
	{x=_x;y=_y;id=_id;}
};
struct Node
{
	int v,id;
	Node(int _v=0,int _id=0)
	{v=_v;id=_id;}
	bool operator < (const Node &t)const
	{return v<t.v;}
};
int Dis(Point A,Point B)
{return max(abs(A.x-B.x),abs(A.y-B.y));}

long long ans;
int N,A,B,R;
map<int,set<Node>> sX,sY;
map<int,vector<Node>> vX,vY;
vector<int> ansP;
Point P[MAXN];

queue<int> Q;

int main()
{
	cin>>N>>A>>B;
	for(int i=1;i<=N;i++)
	{
		int x,y,nx,ny;
		cin>>x>>y;
		nx=x-y;
		ny=x+y;
		P[i]=Point(nx,ny,i);
		if(i!=A&&i!=B)
		{
			sX[nx].insert(Node(ny,i));
			sY[ny].insert(Node(nx,i));
		}
		vX[nx].push_back(Node(ny,i));
		vY[ny].push_back(Node(nx,i));
	}
	R=Dis(P[A],P[B]);
	for(auto &it:vX)
		sort(it.second.begin(),it.second.end());
	for(auto &it:vY)
		sort(it.second.begin(),it.second.end());
	
	Q.push(A);
	Q.push(B);
	
	while(!Q.empty())
	{
		int u=Q.front();
		ansP.push_back(u);
		Q.pop();
		if(sX.count(P[u].x+R))
		{
			auto &vec=sX[P[u].x+R];
			auto l=vec.lower_bound(Node(P[u].y-R,0));
			for(auto it=l;it->v<=P[u].y+R&&it!=vec.end();)
			{
				Q.push(it->id);
				sY[P[it->id].y].erase(Node(P[it->id].x,it->id));
				vec.erase(it++);
			}
		}
		if(sX.count(P[u].x-R))
		{
			auto &vec=sX[P[u].x-R];
			auto l=vec.lower_bound(Node(P[u].y-R,0));
			for(auto it=l;it->v<=P[u].y+R&&it!=vec.end();)
			{
				Q.push(it->id);
				sY[P[it->id].y].erase(Node(P[it->id].x,it->id));
				vec.erase(it++);
			}
		}
		if(sY.count(P[u].y+R))
		{
			auto &vec=sY[P[u].y+R];
			auto l=vec.lower_bound(Node(P[u].x-R,0));
			for(auto it=l;it->v<=P[u].x+R&&it!=vec.end();)
			{
				Q.push(it->id);
				sX[P[it->id].x].erase(Node(P[it->id].y,it->id));
				vec.erase(it++);
			}
		}
		if(sY.count(P[u].y-R))
		{
			auto &vec=sY[P[u].y-R];
			auto l=vec.lower_bound(Node(P[u].x-R,0));
			for(auto it=l;it->v<=P[u].x+R&&it!=vec.end();)
			{
				Q.push(it->id);
				sX[P[it->id].x].erase(Node(P[it->id].y,it->id));
				vec.erase(it++);
			}
		}
	}
	
	for(auto u:ansP)
	{
		if(vX.count(P[u].x+R))
		{
			auto &vec=vX[P[u].x+R];
			auto l=lower_bound(vec.begin(),vec.end(),Node(P[u].y-R,0));
			auto r=upper_bound(vec.begin(),vec.end(),Node(P[u].y+R,0));
			ans+=r-l;
		}
		if(vX.count(P[u].x-R))
		{
			auto &vec=vX[P[u].x-R];
			auto l=lower_bound(vec.begin(),vec.end(),Node(P[u].y-R,0));
			auto r=upper_bound(vec.begin(),vec.end(),Node(P[u].y+R,0));
			ans+=r-l;
		}
		if(vY.count(P[u].y+R))
		{
			auto &vec=vY[P[u].y+R];
			auto l=lower_bound(vec.begin(),vec.end(),Node(P[u].x-R+1,0));
			auto r=upper_bound(vec.begin(),vec.end(),Node(P[u].x+R-1,0));
			ans+=r-l;
		}
		if(vY.count(P[u].y-R))
		{
			auto &vec=vY[P[u].y-R];
			auto l=lower_bound(vec.begin(),vec.end(),Node(P[u].x-R+1,0));
			auto r=upper_bound(vec.begin(),vec.end(),Node(P[u].x+R-1,0));
			ans+=r-l;
		}
	}
	
	ans/=2;
	cout<<ans<<endl;
	
	return 0;
}

