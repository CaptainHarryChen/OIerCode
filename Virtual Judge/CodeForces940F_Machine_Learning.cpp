#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=200005;

struct query
{int l,r,ti,id;};

int N,OP,blksiz,q,m;
int a[MAXN];

bool CaptainMo(query a,query b)
{
	a.l/=blksiz;a.r/=blksiz;
	b.l/=blksiz;b.r/=blksiz;
	if(a.l==b.l)
		return a.r<b.r||(a.r==b.r&&a.ti<b.ti);
	return a.l<b.l;
}

int n;
int ans[MAXN];
query que[MAXN];
int mod[MAXN][3];

void Discretization()
{
	static int t[MAXN*2];
	for(int i=1;i<=N;i++)
		t[i]=a[i];
	for(int i=1;i<=m;i++)
		t[i+N]=mod[i][1];
	sort(t+1,t+N+m+1);
	n=unique(t+1,t+N+m+1)-t-1;
	for(int i=1;i<=N;i++)
		a[i]=lower_bound(t+1,t+n+1,a[i])-t;
	for(int i=1;i<=m;i++)
	{
		mod[i][1]=lower_bound(t+1,t+n+1,mod[i][1])-t;
		mod[i][2]=lower_bound(t+1,t+n+1,mod[i][2])-t;
	}
}

int l,r,t,tans;
int cnt1[MAXN],cnt2[MAXN];

void add(int x)
{
	cnt2[cnt1[x]]--;
	if(cnt1[x]!=0&&cnt2[cnt1[x]]==0)
		tans=min(tans,cnt1[x]);
	cnt1[x]++;
	cnt2[cnt1[x]]++;
	if(tans==cnt1[x])
		while(cnt2[tans]>0)
			tans++;
}
void del(int x)
{
	cnt2[cnt1[x]]--;
	if(cnt1[x]!=0&&cnt2[cnt1[x]]==0)
		tans=min(tans,cnt1[x]);
	cnt1[x]--;
	cnt2[cnt1[x]]++;
	if(tans==cnt1[x])
		while(cnt2[tans]>0)
			tans++;
}
void go()
{
	t++;
	if(l<=mod[t][0]&&mod[t][0]<=r)
	{
		del(mod[t][2]);
		add(mod[t][1]);
	}
	a[mod[t][0]]=mod[t][1];
}
void back()
{
	if(l<=mod[t][0]&&mod[t][0]<=r)
	{
		del(mod[t][1]);
		add(mod[t][2]);
	}
	a[mod[t][0]]=mod[t][2];
	t--;
}

int main()
{
	scanf("%d%d",&N,&OP);
	blksiz=pow(N,2.0/3.0);
	
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	for(int i=1,op;i<=OP;i++)
	{
		scanf("%d",&op);
		if(op==2)
			m++,scanf("%d%d",mod[m],mod[m]+1);
		else
			q++,scanf("%d%d",&que[q].l,&que[q].r),que[q].ti=m,que[q].id=q;
	}
	
	Discretization();
	
	for(int i=1;i<=m;i++)
		mod[i][2]=a[mod[i][0]],a[mod[i][0]]=mod[i][1];
	for(int i=m;i>0;i--)
		a[mod[i][0]]=mod[i][2];
	sort(que+1,que+q+1,CaptainMo);
	
	l=1,r=1,t=0,tans=2;
	cnt1[a[1]]=1;cnt2[0]=n-1;cnt2[1]=1;
	
	for(int i=1;i<=q;i++)
	{
		while(t<que[i].ti)
			go();
		while(t>que[i].ti)
			back();
		while(r<que[i].r)
			r++,add(a[r]);
		while(l>que[i].l)
			l--,add(a[l]);
		while(r>que[i].r)
			del(a[r]),r--;
		while(l<que[i].l)
			del(a[l]),l++;
			
		ans[que[i].id]=tans;
	}
	
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
		
	return 0;
}
