#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=1005,MAXM=MAXN*MAXN;

struct Edge
{
	int v;
	Edge *nxt;
}E[MAXM*2],*adj[MAXN],*ncnt=E;
void add_edge(int u,int v)
{
	ncnt->v=v;
	ncnt->nxt=adj[u];
	adj[u]=ncnt++;
}

struct Ans
{
	int step;
	char add[10];
	Ans(){}
	Ans(int stp,char str[])
	{
		step=stp;
		strcpy(add,str);
	}
	bool operator < (const Ans &t)const
	{
		if(step<t.step)
			return true;
		if(step>t.step)
			return false;
		for(int i=0;add[i];i++)
		{
			if(add[i]<t.add[i])
				return true;
			if(add[i]>t.add[i])
				return false;
		}
		return true;
	}
}ans,temp;

int n,len;
char str[MAXN][10],ads[MAXM][10];
int ad[MAXM][2],adc;
int d1[MAXN],d2[MAXN];
bool mk[MAXN];

void check_edge(int a,int b)
{
	int cnt=0;
	for(int i=0;i<len;i++)
		cnt+=str[a][i]!=str[b][i];
	if(cnt==1)
	{
		add_edge(a,b);
		add_edge(b,a);
	}
	if(cnt==2)
	{
		adc++;
		ad[adc][0]=a;
		ad[adc][1]=b;
		int d[2];
		for(int i=0,j=0;i<len;i++)
			if(str[a][i]!=str[b][i])
				d[j++]=i;
		strcpy(ads[adc],str[a]);
		if(str[a][d[0]]<str[b][d[0]])
			ads[adc][d[1]]=str[b][d[1]];
		else
			ads[adc][d[0]]=str[b][d[0]];
	}
}
void BFS(int st,int d[])
{
	queue<int> Q;
	memset(d+1,0x3F,sizeof(int)*n);
	d[st]=0;
	Q.push(st);
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(Edge *p=adj[u];p;p=p->nxt)
			if(d[p->v]==0x3F3F3F3F)
			{
				d[p->v]=d[u]+1;
				Q.push(p->v);
			}
	}
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		memset(mk,0,sizeof mk);
		ncnt=E;
		memset(adj,0,sizeof adj);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str[i]);
			for(int j=1;j<i&&mk[i]==false;j++)
				if(strcmp(str[j],str[i])==0)
					mk[i]=true;
		}
		if(mk[2])
		{
			printf("0\n0\n");
			continue;
		}
		len=strlen(str[1]);
		adc=0;
		for(int i=1;i<=n;i++)
		{
			if(mk[i])continue;
			for(int j=i+1;j<=n;j++)
				if(!mk[j])
					check_edge(i,j);
		}
		BFS(1,d1);
		BFS(2,d2);
		ans.step=min(d1[2],d2[1]);
		ans.add[0]=0;
		for(int i=1;i<=adc;i++)
		{
			temp=Ans(min(d1[ad[i][0]]+2+d2[ad[i][1]],d2[ad[i][0]]+2+d1[ad[i][1]]),ads[i]);
			ans=min(ans,temp);
		}
		if(ans.add[0]==0)
			puts("0");
		else
			puts(ans.add);
		printf("%d\n",ans.step>=0x3F3F3F3F?-1:ans.step);
	}
	return 0;
}
