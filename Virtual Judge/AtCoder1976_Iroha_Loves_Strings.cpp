#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
const int MAXN=2005,MAXK=10005,MAXS=1000005;

int N,K;
char str[MAXN][MAXK];
int len[MAXN];
bitset<MAXK> dp[MAXN];
pair<int,int> ch[2][MAXK];
int cnt,ncnt;

int main()
{
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%s",str[i]);
		len[i]=strlen(str[i]);
	}
	dp[N+1][0]=1;
	for(int i=N;i>0;i--)
		dp[i]=dp[i+1]|(dp[i+1]<<len[i]);
		
	for(int i=1;i<=N;i++)
		if(dp[i+1][K-len[i]])
			ch[0][cnt++]=(make_pair(i,0));
	
	for(int ii=1,i=1;ii<=K;ii++,i^=1)
	{
		ncnt=0;
		char minc='z';
		for(int j=0;j<cnt;j++)
			minc=min(minc,str[ch[i^1][j].first][ch[i^1][j].second]);
		putchar(minc);
		int minid=N+1;
		for(int j=0;j<cnt;j++)
		{
			int id=ch[i^1][j].first,pos=ch[i^1][j].second;
			if(str[id][pos]!=minc)
				continue;
			if(pos<len[id]-1)
				ch[i][ncnt++]=(make_pair(id,pos+1));
			else
				minid=min(minid,id);
		}
		for(int j=minid+1;j<=N;j++)
			if(K-ii-len[j]>=0&&dp[j+1][K-ii-len[j]])
				ch[i][ncnt++]=(make_pair(j,0));
		cnt=ncnt;
	}
	puts("");
	
	return 0;
}
