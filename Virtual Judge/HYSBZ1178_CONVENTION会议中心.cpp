#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXLOG=20;

struct Seg
{
	int l,r,id;
	Seg(int l=0,int r=0):l(l),r(r){}
	bool operator < (const Seg &b)const
	{return l<b.l||(l==b.l&&r<b.r);}
};

bool cmp2(Seg a,Seg b)
{return a.r<b.r||(a.r==b.r&&a.l<b.l);}
bool cmp3(Seg a,Seg b)
{return a.id<b.id;}

int n;
Seg s[MAXN],t[MAXN];
set< pair<int,bool> > S;
int f[MAXN][MAXLOG];

int getans(int l,int r)
{
	int i=lower_bound(s+1,s+n+1,Seg(l,0))-s;
	if(i>n)
		return 0;
	int ret=0;
	for(int j=MAXLOG-1;j>=0;j--)
		if(f[i][j]!=-1&&f[i][j]<=r)
		{
			ret+=(1<<j);
			i=lower_bound(s+1,s+n+1,Seg(f[i][j]+1,0))-s;
		}
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].l,&s[i].r),s[i].id=i;
	sort(s+1,s+n+1);
	memset(f,-1,sizeof f);
	for(int i=n;i>0;i--)
	{
		f[i][0]=f[i+1][0];
		if(f[i][0]==-1||f[i][0]>s[i].r)
			f[i][0]=s[i].r;
	}
	for(int j=1;j<MAXLOG;j++)
		for(int i=n+1-(1<<j);i>0;i--)
		{
			f[i][j]=f[i+1][j];
			if(f[i][j-1]!=-1)
			{
				int k=lower_bound(s+1,s+n+1,Seg(f[i][j-1]+1,0))-s;
				if(f[k][j-1]!=-1)
					if(f[i][j]==-1||f[i][j]>f[k][j-1])
						f[i][j]=f[k][j-1];
			}
		}
			
	int ans=getans(0,0x7FFFFFFF);
	printf("%d\n",ans);
	memcpy(t,s,sizeof s);
	sort(t+1,t+n+1,cmp3);
	S.insert(make_pair(0,1));
	S.insert(make_pair(0x7FFFFFFF,0));
	for(int i=1;i<=n;i++)
	{
		set< pair<int,bool> >::iterator il,ir;
		int l,r;
		il=S.lower_bound(make_pair(t[i].l,0));
		if(il->first<=t[i].r||il->second==1)
			continue;
		il--;
		l=il->first;
		ir=S.lower_bound(make_pair(t[i].r,1));
		r=ir->first;
		int tmp=getans(l+1,t[i].l-1)+1+getans(t[i].r+1,r-1);
		if(tmp!=getans(l+1,r-1))
			continue;
		S.insert(make_pair(t[i].l,0));
		S.insert(make_pair(t[i].r,1));
		printf("%d ",i);
	}
	puts("");
	
	return 0;
}
