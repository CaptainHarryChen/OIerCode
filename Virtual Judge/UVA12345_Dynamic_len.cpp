#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=50005,MAXA=1000005;

struct query
{int l,r,ti,id;};

int N,OP,blksiz,q,m;
int a[MAXN],mod[MAXN][3];

int ans[MAXN];
query que[MAXN];

bool CaptainMo(query a,query b)
{
	a.l/=blksiz;a.r/=blksiz;
	b.l/=blksiz;b.r/=blksiz;
	if(a.l==b.l)
		return a.r<b.r||(a.r==b.r&&a.ti<b.ti);
	return a.l<b.l;
}

int l,r,t,tans;
int cnt[MAXA];
void add(int x)
{
	cnt[x]++;
	tans+=(cnt[x]==1);
}
void del(int x)
{
	cnt[x]--;
	tans-=(cnt[x]==0);
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
	for(int i=1;i<=OP;i++)
	{
		char op[5];
		scanf("%s",op);
		if(op[0]=='M')
			m++,scanf("%d%d",mod[m],mod[m]+1),mod[m][0]++;
		else
			q++,scanf("%d%d",&que[q].l,&que[q].r),que[q].ti=m,que[q].id=q,que[q].l++;
	}
	for(int i=1;i<=m;i++)
		mod[i][2]=a[mod[i][0]],a[mod[i][0]]=mod[i][1];
	for(int i=m;i>0;i--)
		a[mod[i][0]]=mod[i][2];
	sort(que+1,que+q+1,CaptainMo);
	l=1,r=1,t=0,tans=1;
	cnt[a[1]]=1;
	for(int i=1;i<=q;i++)
	{
		while(t<que[i].ti)
			go();
		while(t>que[i].ti)
			back();
		while(l<que[i].l)
			del(a[l]),l++;
		while(l>que[i].l)
			l--,add(a[l]);
		while(r<que[i].r)
			r++,add(a[r]);
		while(r>que[i].r)
			del(a[r]),r--;
		ans[que[i].id]=tans;
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
