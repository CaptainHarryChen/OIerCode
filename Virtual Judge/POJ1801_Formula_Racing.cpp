#include<cstdio>
const int MAXL=1005,MAXC=10005;
const int dir[8][2]={{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};

struct data
{int x,y,d,s,t;};

int w,h;
char tra[MAXL][MAXL];
char cmd[MAXC];
int hcnt;
data st,ed,hit[MAXC];

void simulate()
{
	hcnt=0;
	data now=st;
	now.s=0;
	now.t=0;
	for(int i=0;cmd[i];i++)
	{
		if(cmd[i]=='a')
		{
			if(now.s<st.s)
				now.s++;
		}
		else if(cmd[i]=='b')
		{
			if(now.s>0)
				now.s--;
		}
		else if(cmd[i]=='l')
			now.d=(now.d+7)%8;
		else if(cmd[i]=='r')
			now.d=(now.d+1)%8;
		bool nonroad=false;
		for(int j=1;j<=now.s;j++)
		{
			now.x+=dir[now.d][0];
			now.y+=dir[now.d][1];
			if(tra[now.y][now.x]=='.')
				nonroad=true;
			else if(tra[now.y][now.x]=='s')
				hit[++hcnt]=now;
			else if(tra[now.y][now.x]=='W')
			{ed=now;ed.t=-1;return;}
		}
		if(nonroad&&now.s>1)
			now.s=1;
		now.t++;
	}
	ed=now;
}

int main()
{
	int T,n;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		scanf("%d%d",&w,&h);
		for(int i=0;i<h;i++)
			scanf("%s",tra[i]);
		printf("Scenario #%d:\n",Case);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d%s",&st.x,&st.y,&st.d,&st.s,cmd);
			simulate();
			printf("%d %d %d %d",ed.x,ed.y,ed.d,ed.s);
			if(ed.t==-1)puts(" crashed");
			else puts("");
			for(int j=1;j<=hcnt;j++)
				printf("crossing startline: %d %d %d %d %d\n",hit[j].x,hit[j].y,hit[j].d,hit[j].s,hit[j].t);
		}
		puts("");
	}
	return 0;
}
