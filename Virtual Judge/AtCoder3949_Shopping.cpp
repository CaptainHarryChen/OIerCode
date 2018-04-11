#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005;

bool state[MAXN][2];
bool used[MAXN];
int x[MAXN],t[MAXN];
int st00[MAXN],tp00;
int st01[MAXN],tp01;

int main()
{
	int N,L,ans=0;
	scanf("%d%d",&N,&L);
	for(int i=1;i<=N;i++)
		scanf("%d",x+i);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",t+i);
		ans+=(t[i]/(2*L));
		t[i]%=2LL*L;
	}
	for(int i=1;i<=N;i++)
	{
		if(t[i]==0)
			state[i][0]=state[i][1]=1;
		else
		{
			state[i][0]=t[i]>(L-x[i])*2;
			state[i][1]=t[i]>x[i]*2;
			if(state[i][0]&&state[i][1])
				ans++;
		}
	}
	for(int i=N-1;i>0;i--)
	{
		if(state[i][0]==0&&state[i][1]==0)
		{
			if(tp01)
				used[st01[tp01--]]=used[i]=true,ans++;
			else
				st00[++tp00]=i;
		}
		if(state[i][0]==1&&state[i][1]==0)
			if(tp00)
				used[st00[tp00--]]=used[i]=true,ans++;
		if(state[i][0]==0&&state[i][1]==1)
			st01[++tp01]=i;
	}
	while(tp00>=2)
		used[st00[tp00]]=used[st00[tp00-1]]=true,tp00-=2,ans++;
	for(int i=1;i<N;i++)
		if(!used[i])
		{
			if(state[i][0]==0&&state[i][1]==0&&state[N][0]==0)
			{
				used[i]=used[N]=true,ans++;
				break;
			}
			if(state[i][0]==1&&state[i][0]==0&&state[N][0]==0&&state[N][1]==0)
			{
				used[i]=used[N]=true,ans++;
				break;
			}
		}
	int S=0;
	for(int i=1;i<=N;i++)
		if((state[i][0]==0||state[i][1]==0)&&!used[i])
			S++;
	int last=0;
	for(int i=1;i<=N;i++)
		if(state[i][0]==0&&!used[i])
			last=i;
	if(last!=N)
		ans+=S+1;
	if(last==N)
		ans+=S;

	printf("%lld\n",1LL*ans*(2LL*L));
	
	return 0;
}
