#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 1005
#define MAXLEN 10
char dic[MAXN][MAXLEN],s[MAXLEN],t[MAXLEN];
int n=1,step[MAXN];
bool vis[MAXN];
bool check(char s1[],char s2[])
{
	int cnt=0;
	for(int i=0;s1[i];i++)
		if(s1[i]!=s2[i])
		{cnt++;if(cnt>1)return 0;}
	return 1;
}
int bfs()
{
	queue<int>q;
	memset(step,127,sizeof step);
	q.push(0);
	vis[0]=1;
	step[0]=1;
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		char temp[MAXLEN];
		strcpy(temp,dic[t]);
		for(int i=1;i<=n;i++)
			if(!vis[i]&&check(temp,dic[i])&&step[i]>step[t]+1)
			{
				if(i==n)return step[t]+1;
				q.push(i);
				vis[i]=1;
				step[i]=step[t]+1;
			}
	}
	return 0;
}
int main()
{
	scanf("%s%s",s,t);
	while(~scanf("%s",dic[n]))
		n++;
	strcpy(dic[n],t);
	strcpy(dic[0],s);
	printf("%d\n",bfs());
	return 0;
}
