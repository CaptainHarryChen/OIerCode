#include<cstdio>
#include<bitset>
#include<algorithm>
using namespace std;
const int MAXN=505,MAXM=100005;

int N,M;
bitset<MAXN> alive[MAXN];
bool dead[MAXN];
int x[MAXM],y[MAXM];

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=N;i++)
	{
		alive[i][i]=1;
		for(int j=M;j>=1;j--)
			if(alive[i][x[j]]&&alive[i][y[j]])
			{
				dead[i]=true;
				break;
			}
			else if(alive[i][x[j]])
				alive[i][y[j]]=1;
			else if(alive[i][y[j]])
				alive[i][x[j]]=1;
	}
	int ans=0;
	for(int i=1;i<=N;i++)
		for(int j=i+1;j<=N;j++)
			if(!dead[i]&&!dead[j]&&(alive[i]&alive[j]).none())
				ans++;
	printf("%d\n",ans);
	
	return 0;
}
