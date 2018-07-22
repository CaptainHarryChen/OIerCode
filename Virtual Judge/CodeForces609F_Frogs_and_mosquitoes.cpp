#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=200005,BLKSIZ=550;
typedef pair<long long,int> Mos;

struct Frog
{
	int x;
	long long t;
	int id;
	Frog(){}
	Frog(int x,long long t,int id):x(x),t(t),id(id){}
	bool operator < (const Frog &y)const
	{
		return x<y.x;
	}
};

int n,m;
int cnt[MAXN];
long long t[MAXN],best[MAXN];
Frog frogs[MAXN];
multiset<Mos> moses;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%I64d",&frogs[i].x,&frogs[i].t),frogs[i].id=i,t[i]=frogs[i].t;
	sort(frogs+1,frogs+n+1);
	for(int i=1;i<=n;i++)
		best[i/BLKSIZ]=max(best[i/BLKSIZ],frogs[i].x+frogs[i].t);
	for(int i=1,p,b;i<=m;i++)
	{
		scanf("%d%d",&p,&b);
		
		int id,ff=-1;
		
		for(int blk=0;blk*BLKSIZ<=n&&frogs[blk*BLKSIZ].x<=p;blk++)
			if(best[blk]>=p)
			{
				for(int i=max(blk*BLKSIZ,1);i<blk*BLKSIZ+BLKSIZ&&i<=n;i++)
					if((ff==-1||frogs[ff].x>frogs[i].x)&&frogs[i].x+frogs[i].t>=p)
						ff=i;
				id=blk;
				break;
			}
		
		if(ff==-1||frogs[ff].x>p)
			moses.insert(Mos(p,b));
		else
		{
			set<Mos>::iterator mit=moses.lower_bound(Mos(frogs[ff].x+frogs[ff].t,0));
			for(;;)
			{
				cnt[frogs[ff].id]++;
				t[frogs[ff].id]+=b;
				frogs[ff].t+=b;
				if(mit==moses.end()||mit->first>frogs[ff].x+frogs[ff].t)
					break;
				p=mit->first;
				b=mit->second;
				moses.erase(mit++);
			}
			best[id]=max(best[id],frogs[ff].x+frogs[ff].t);
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d %I64d\n",cnt[i],t[i]);
	
	return 0;
}
