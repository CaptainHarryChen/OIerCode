#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#define MAXN 10
using namespace std;
char s[MAXN*MAXN];
int n,minans=999999,ans[MAXN],t[MAXN],m1[30],m2[MAXN];
bool vis[MAXN],mm[30];
struct node
{
	bool con[MAXN];
	int x,cnt;
	node(){memset(con,0,sizeof con);}
}G[MAXN];
void dfs(int k)
{
	if(k>n)
	{
		int maxbd=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(G[i].con[j])
					maxbd=max(maxbd,abs(G[i].x-G[j].x));
		if(maxbd<minans)
		{
			minans=maxbd;
			memcpy(ans,t,sizeof t);
		}
		return;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			if(G[i].cnt>minans)
				continue;
			bool f=1;
			for(int j=1;j<=n;j++)
				if(G[i].con[j]&&vis[j])
					if(k-G[j].x>=minans)
					{f=0;break;}
			if(!f)break;
			vis[i]=1;
			t[k]=i;
			G[i].x=k;
			for(int j=1;j<=n;j++)
				G[j].cnt-=G[j].con[i];
			dfs(k+1);
			vis[i]=0;
			t[k]=0;
			G[i].x=0;
			for(int j=1;j<=n;j++)
				G[j].cnt+=G[j].con[i];
		}
}
int main()
{
	while(1)
	{
		memset(mm,0,sizeof mm);
		memset(G,0,sizeof G);
		minans=9999999;
		n=0;
		scanf("%s",s);
		if(s[0]=='#')break;
		for(int i=0,len=strlen(s);i<len;i++)
			if(s[i]>='A'&&s[i]<='Z')
				mm[s[i]-'A']=1;
		for(int i=0;i<26;i++)
			if(mm[i])
			{m1[i]=++n;m2[n]=i+'A';}
		for(int i=0,len=strlen(s),flag=1,x,y;i<len;i++)
		{
			if(s[i]==':')flag=0;
			else if(s[i]==';')flag=1;
			else if(flag)
				x=m1[s[i]-'A'];
			else
			{
				y=m1[s[i]-'A'];
				G[x].con[y]=1;
				G[x].cnt++;
			}
		}
		dfs(1);
		for(int i=1;i<=n;i++)
			printf("%c ",m2[ans[i]]);
		printf("-> %d\n",minans);
	}
	return 0;
}
