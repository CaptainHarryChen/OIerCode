#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200010;
struct Bird
{
	int id;
	long long x,y;
	inline void read()
	{scanf("%lld%lld",&x,&y);}
};
bool Bird_cmpx_g(Bird a,Bird b)
{return a.x<b.x||(a.x==b.x&&a.y<b.y);}
bool Bird_cmpy_g(Bird a,Bird b)
{return a.y<b.y||(a.y==b.y&&a.x<b.x);}
bool Bird_cmpx_l(Bird a,Bird b)
{return a.x>b.x||(a.x==b.x&&a.y>b.y);}
bool Bird_cmpy_l(Bird a,Bird b)
{return a.y>b.y||(a.y==b.y&&a.x>b.x);}
struct Wall
{
	int id;
	Bird a,b;
	inline void read()
	{a.read();b.read();}
	inline bool mode()
	{return a.x==b.x;}
};
bool Wall_cmpx_g(Wall a,Wall b)
{return Bird_cmpx_g(a.a,b.a);}
bool Wall_cmpy_g(Wall a,Wall b)
{return Bird_cmpy_g(a.a,b.a);}
bool Wall_cmpx_l(Wall a,Wall b)
{return Bird_cmpx_l(a.a,b.a);}
bool Wall_cmpy_l(Wall a,Wall b)
{return Bird_cmpy_l(a.a,b.a);}
class SegTree
{
	static int N;
	int wid[MAXN*12];
public:
	inline void Init(int n)
	{
		memset(wid,0,sizeof wid);
		N=n;
	}
	void Insert(int L,int R,int val,int id=1,int l=0,int r=N)
	{
		if(r<L||R<l)
			return;
		if(L<=l&&r<=R)
		{
			wid[id]=val;
			return;
		}
		if(wid[id]!=-1)
			wid[id*2]=wid[id*2+1]=wid[id];
		Insert(L,R,val,id*2,l,(l+r)/2);
		Insert(L,R,val,id*2+1,(l+r)/2+1,r);
		if(wid[id*2]==-1||wid[id*2+1]==-1||wid[id*2]!=wid[id*2+1])
			wid[id]=-1;
	}
	int Query(int pos,int id=1,int l=0,int r=N)
	{
		if(r<pos||pos<l)
			return -1;
		if(wid[id]!=-1)
			return wid[id];
		int q1=Query(pos,id*2,l,(l+r)/2);
		int q2=Query(pos,id*2+1,(l+r)/2+1,r);
		if(q1==-1)return q2;
		return q1;
	}
};
Wall wall[MAXN];
Bird bird[MAXN];
long long mapx[MAXN*3],mapy[MAXN*3];
int x_cnt,y_cnt;
long long dis[MAXN];
int ans[MAXN],hitid[MAXN];
SegTree ST;
int SegTree::N;
int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	//输入，初始化，记录x，y，用于离散化
	for(int i=1;i<=N;i++)
	{
		wall[i].read();
		wall[i].id=i;
		mapx[x_cnt++]=wall[i].a.x;
		mapx[x_cnt++]=wall[i].b.x;
		mapy[y_cnt++]=wall[i].a.y;
		mapy[y_cnt++]=wall[i].b.y;
	}
	for(int i=1;i<=M;i++)
	{
		bird[i].read();
		bird[i].id=i;
		mapx[x_cnt++]=bird[i].x;
		mapy[y_cnt++]=bird[i].y;
	}
	memset(dis,0x7F,sizeof dis);
	//排序，离散化墙，鸟的坐标
	sort(mapx,mapx+x_cnt);
	sort(mapy,mapy+y_cnt);
	for(int i=1;i<=N;i++)
	{
		wall[i].a.x=lower_bound(mapx,mapx+x_cnt,wall[i].a.x)-mapx;
		wall[i].a.y=lower_bound(mapy,mapy+y_cnt,wall[i].a.y)-mapy;
		wall[i].b.x=lower_bound(mapx,mapx+x_cnt,wall[i].b.x)-mapx;
		wall[i].b.y=lower_bound(mapy,mapy+y_cnt,wall[i].b.y)-mapy;
	}
	for(int i=1;i<=M;i++)
	{
		bird[i].x=lower_bound(mapx,mapx+x_cnt,bird[i].x)-mapx;
		bird[i].y=lower_bound(mapy,mapy+y_cnt,bird[i].y)-mapy;
	}
	int wid,bid;
	//设置墙同一直线总是坐标小的在前，方便排序
	for(int i=1;i<=N;i++)
	{
		if(wall[i].mode()&&wall[i].a.y>wall[i].b.y)
			swap(wall[i].a.y,wall[i].b.y);
		if(!wall[i].mode()&&wall[i].a.x>wall[i].b.x)
			swap(wall[i].a.x,wall[i].b.x);
	}
	//初始化，按x从小到大排序
	wid=bid=1;
	ST.Init(3*N);
	sort(wall+1,wall+N+1,Wall_cmpx_g);
	sort(bird+1,bird+M+1,Bird_cmpx_g);
	//扫描线，从左到右，从下到上，鸟向左撞
	while(wid<=N||bid<=M)
	{
		//添加墙的地盘
		if(wid<=N&&(bid>M||Bird_cmpx_g(wall[wid].a,bird[bid])))
		{
			ST.Insert(wall[wid].a.y,wall[wid].b.y,wid);
			wid++;
		}
		//更新鸟的答案
		else if(bid<=M)
		{
			int qid=ST.Query(bird[bid].y);
			if(qid!=0)
			{
				long long d=max(0LL,mapx[bird[bid].x]-mapx[wall[qid].b.x]);
				if(d<dis[bird[bid].id])
				{
					if(dis[bird[bid].id]!=0x7F7F7F7F7F7F7F7FLL)
						ans[hitid[bird[bid].id]]--;
					ans[wall[qid].id]++;
					dis[bird[bid].id]=d;
					hitid[bird[bid].id]=wall[qid].id;
				}
			}
			bid++;
		}
	}
	//初始化，按y从小到大排序
	wid=bid=1;
	ST.Init(3*N);
	sort(wall+1,wall+N+1,Wall_cmpy_g);
	sort(bird+1,bird+M+1,Bird_cmpy_g);
	//扫描线，从下到上，从左到右，鸟向下撞
	while(wid<=N||bid<=M)
	{
		//添加墙的地盘
		if(wid<=N&&(bid>M||Bird_cmpy_g(wall[wid].a,bird[bid])))
		{
			ST.Insert(wall[wid].a.x,wall[wid].b.x,wid);
			wid++;
		}
		//更新鸟的答案
		else if(bid<=M)
		{
			int qid=ST.Query(bird[bid].x);
			if(qid!=0)
			{
				long long d=max(0LL,mapy[bird[bid].y]-mapy[wall[qid].b.y]);
				if(d<dis[bird[bid].id])
				{
					if(dis[bird[bid].id]!=0x7F7F7F7F7F7F7F7FLL)
						ans[hitid[bird[bid].id]]--;
					ans[wall[qid].id]++;
					dis[bird[bid].id]=d;
					hitid[bird[bid].id]=wall[qid].id;
				}
			}
			bid++;
		}
	}
	//设置墙同一直线总是坐标大的在前，方便排序
	for(int i=1;i<=N;i++)
	{
		if(wall[i].mode()&&wall[i].a.y<wall[i].b.y)
			swap(wall[i].a.y,wall[i].b.y);
		if(!wall[i].mode()&&wall[i].a.x<wall[i].b.x)
			swap(wall[i].a.x,wall[i].b.x);
	}
	//初始化，按x从大到小排序
	wid=bid=1;
	ST.Init(3*N);
	sort(wall+1,wall+N+1,Wall_cmpx_l);
	sort(bird+1,bird+M+1,Bird_cmpx_l);
	//扫描线，从右到左，从上到下，鸟向右撞
	while(wid<=N||bid<=M)
	{
		//添加墙的地盘
		if(wid<=N&&(bid>M||Bird_cmpx_l(wall[wid].a,bird[bid])))
		{
			ST.Insert(wall[wid].b.y,wall[wid].a.y,wid);
			wid++;
		}
		//更新鸟的答案
		else if(bid<=M)
		{
			int qid=ST.Query(bird[bid].y);
			if(qid!=0)
			{
				long long d=max(0LL,mapx[wall[qid].b.x]-mapx[bird[bid].x]);
				if(d<dis[bird[bid].id])
				{
					if(dis[bird[bid].id]!=0x7F7F7F7F7F7F7F7FLL)
						ans[hitid[bird[bid].id]]--;
					ans[wall[qid].id]++;
					dis[bird[bid].id]=d;
					hitid[bird[bid].id]=wall[qid].id;
				}
			}
			bid++;
		}
	}
	//初始化，按y从大到小排序
	wid=bid=1;
	ST.Init(3*N);
	sort(wall+1,wall+N+1,Wall_cmpy_l);
	sort(bird+1,bird+M+1,Bird_cmpy_l);
	//扫描线，从上到下，从右到左，鸟向下撞
	while(wid<=N||bid<=M)
	{
		//添加墙的地盘
		if(wid<=N&&(bid>M||Bird_cmpy_l(wall[wid].a,bird[bid])))
		{
			ST.Insert(wall[wid].b.x,wall[wid].a.x,wid);
			wid++;
		}
		//更新鸟的答案
		else if(bid<=M)
		{
			int qid=ST.Query(bird[bid].x);
			if(qid!=0)
			{
				long long d=max(0LL,mapy[wall[qid].b.y]-mapy[bird[bid].y]);
				if(d<dis[bird[bid].id])
				{
					if(dis[bird[bid].id]!=0x7F7F7F7F7F7F7F7FLL)
						ans[hitid[bird[bid].id]]--;
					ans[wall[qid].id]++;
					dis[bird[bid].id]=d;
					hitid[bird[bid].id]=wall[qid].id;
				}
			}
			bid++;
		}
	}
	//输出
	for(int i=1;i<=N;i++)
		printf("%d\n",ans[i]);
	return 0;
}
