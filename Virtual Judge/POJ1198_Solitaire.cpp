#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=10,MAXS=1677320,MAXHASH=92083;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

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

	void Clear()
	{
		_new=node;
		memset(adj,0,sizeof adj);
	}
	void Set(int id,int val)
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
	int Get(int id)
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
	bool operator < (const Pos &t)const
	{return x<t.x||(x==t.x&&y<t.y);}
	bool operator == (const Pos &t)const
	{return x==t.x&&y==t.y;}
	void move(int d)
	{
		x+=dir[d][0];
		y+=dir[d][1];
	}
};
struct State {
	Pos p[4];
	State(){}
	State(const Pos _p[])
	{p[0]=_p[0];p[1]=_p[1];p[2]=_p[2];p[3]=_p[3];}
	bool operator == (State t)
	{
		sort(p,p+4);
		sort(t.p,t.p+4);
		for(int i=0;i<4;i++)
			if(!(p[i]==t.p[i]))
				return false;
		return true;
	}
};
struct StateCode {
	int sc;
	bool type;
	StateCode(int sc,bool type):sc(sc),type(type){}
};

int w=8,h=8,n=4;

int encode(State s) {
	sort(s.p,s.p+n);
	int res=0;
	for(int i=0;i<n;i++)
	{
		res<<=6;
		res|=(s.p[i].x-1)*w+s.p[i].y-1;
	}
	return res;
}
State decode(int s) {
	State res;
	for(int i=n-1;i>=0;i--,s>>=6)
		res.p[i]=Pos((s&((1<<6)-1))/w+1,(s&((1<<6)-1))%w+1);
	return res;
}

char map[MAXN][MAXN];
bool check(Pos u) {
	return u.x>0&&u.x<=h&&u.y>0&&u.y<=w;
}
bool check(State b) {
	for(int i=0;i<n;i++)
		if(!check(b.p[i]))
			return false;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(b.p[i]==b.p[j])
				return false;
	return true;
}

HashList step[2];
queue<StateCode> Q;
State st,ed;

bool DoubleBFS()
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
		if(nowstp>=8)
			break;
		State v;
		Q.pop();
		for(int i=0;i<4;i++)
			for(int d=0;d<4;d++)
			{
				v=u;
				v.p[i].move(d);
				for(int j=0;j<4;j++)
					if(i!=j&&v.p[j]==v.p[i])
					{v.p[i].move(d);break;}
				if(!check(v))
					continue;
				int vc=encode(v);
				int stp=step[now.type^1].Get(vc);
				if(stp!=-1&&stp+nowstp+1<=8)
					return true;
				stp=step[now.type].Get(vc);
				if(stp!=-1)
					continue;
				stp=nowstp+1;
				#ifdef DEBUG
					puts("State:");
					for(int j=0;j<n;j++)
						printf("%d %d\n",v.p[j].x,v.p[j].y);
					printf("step:%d\n",stp);
					printf("type:%d\n\n",now.type);
				#endif
				step[now.type].Set(vc,stp);
				Q.push(StateCode(vc,now.type));
			}
	}
	return false;
}

int main()
{
	for(;;)
	{
		for(int i=0;i<n;i++)
			if(scanf("%d%d",&st.p[i].x,&st.p[i].y)==EOF)
				exit(0);
		for(int i=0;i<n;i++)
			scanf("%d%d",&ed.p[i].x,&ed.p[i].y);
		if(st==ed||DoubleBFS())
			puts("YES");
		else
			puts("NO");
	}
	
	return 0;
}
