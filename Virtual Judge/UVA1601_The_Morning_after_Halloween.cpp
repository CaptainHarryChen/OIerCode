#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=18,MAXS=1700000,MAXHASH=999987;
const int dir[5][2]={{0,0},{-1,0},{0,1},{1,0},{0,-1}};
const int pow5[4]={1,5,25,125};

class HashList {
public:
	struct Node
	{
		int id;
		int val;
		Node *nxt;
	};
	static Node node[MAXS],*_new;
	Node *adj[MAXHASH];

	inline void Clear()
	{
		_new=node;
		memset(adj,0,sizeof adj);
	}
	inline void Set(int id,int val)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
			{
				p->val=val;
				return;
			}
		_new->id=id;
		_new->val=val;
		_new->nxt=adj[pos];
		adj[pos]=_new++;
	}
	inline int Get(int id)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
				return p->val;
		return -1;
	}
};
HashList::Node HashList::node[MAXS],*HashList::_new;

struct Pos {
	int x,y;
	Pos(){}
	Pos(int x,int y):x(x),y(y){}
	inline bool operator == (const Pos &t)const
	{return x==t.x&&y==t.y;}
	inline void move(int d)
	{
		x+=dir[d][0];
		y+=dir[d][1];
	}
};
struct State {
	Pos p[3];
	State(){}
	State(const Pos _p[])
	{p[0]=_p[0];p[1]=_p[1];p[2]=_p[2];}
	inline bool operator == (const State &t)const
	{return p[0]==t.p[0]&&p[1]==t.p[1]&&p[2]==t.p[2];}
};
struct StateCode {
	int sc;
	bool type;
	StateCode(int sc,bool type):sc(sc),type(type){}
};

int w,h,n;

inline int encode(const State &s) {
	int res=0;
	for(register int i=0;i<n;i++)
	{
		res<<=8;
		res|=s.p[i].x*w+s.p[i].y;
	}
	return res;
}
inline State decode(int s) {
	State res;
	for(register int i=n-1;i>=0;i--,s>>=8)
		res.p[i]=Pos((s&((1<<8)-1))/w,(s&((1<<8)-1))%w);
	return res;
}

char map[MAXN][MAXN];
inline bool check(Pos u) {
	return map[u.x][u.y]!='#';
}
inline bool check(State a,State b) {//状态a至状态b是否合法
	for(register int i=0;i<n;i++)
		if(!check(b.p[i]))
			return false;
	for(register int i=0;i<n;i++)
		for(register int j=i+1;j<n;j++)
			if(b.p[i]==b.p[j])
				return false;
	for(register int i=0;i<n;i++)
		for(register int j=i+1;j<n;j++)
			if(a.p[i]==b.p[j]&&b.p[i]==a.p[j])
				return false;
	return true;
}

HashList step[2];
queue<StateCode> Q;
State st,ed;

inline int DoubleBFS()
{
	while(!Q.empty())
		Q.pop();
	step[0].Clear();
	step[1].Clear();
	
	step[0].Set(encode(st),0);
	Q.push(StateCode(encode(st),0));
	step[1].Set(encode(ed),0);
	Q.push(StateCode(encode(ed),1));
	
	while(!Q.empty())
	{
		StateCode now=Q.front();
		State u=decode(now.sc);
		int nowstp=step[now.type].Get(now.sc);
		State v;
		Q.pop();
		for(register int s=1;s<pow5[n];s++)//枚举移动方案
		{
			v=u;
			for(register int i=0,ts=s;i<n;i++,ts/=5)
			{
				int d=ts%5;
				v.p[i].move(d);
			}
			if(!check(u,v))//移动方案是否合法
				continue;
			int vc=encode(v);
			int stp=step[now.type^1].Get(vc);//另一搜索方向是否已有此状态
			if(stp!=-1)
				return nowstp+1+stp;
			stp=step[now.type].Get(vc);
			if(stp!=-1)//此方向已有过此状态
				continue;
			stp=nowstp+1;
			step[now.type].Set(vc,stp);
			Q.push(StateCode(vc,now.type));
		}
	}
	return -1;
}

int main()
{
	for(;;)
	{
		scanf("%d%d%d",&w,&h,&n);
		if(w==0&&h==0&&n==0)
			break;
		fgets(map[0],MAXN,stdin);
		for(register int i=0;i<h;i++)
		{
			fgets(map[i],MAXN,stdin);
			for(register int j=0;j<w;j++)
				switch(map[i][j])
				{
					case 'A':ed.p[0]=Pos(i,j);break;
					case 'B':ed.p[1]=Pos(i,j);break;
					case 'C':ed.p[2]=Pos(i,j);break;
					case 'a':st.p[0]=Pos(i,j);break;
					case 'b':st.p[1]=Pos(i,j);break;
					case 'c':st.p[2]=Pos(i,j);break;
				}
		}
		printf("%d\n",DoubleBFS());
	}
	
	return 0;
}
