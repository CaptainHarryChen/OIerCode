#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXP 10000
bool noprime[MAXP];
queue<int>Q;
int step[MAXP];
int main()
{
	noprime[1]=1;
	for(int i=2;i<MAXP;i++)
		if(!noprime[i])
			for(int j=i*i;j<MAXP;j+=i)
				noprime[j]=1;
	int C,st,ed;
	scanf("%d",&C);
	for(int Case=1;Case<=C;Case++)
	{
		scanf("%d%d",&st,&ed);
		while(!Q.empty())Q.pop();
		memset(step,-1,sizeof step);
		Q.push(st);
		step[st]=0;
		bool success=0;
		while(!Q.empty()&&!success)
		{
			int t=Q.front();
			Q.pop();
			int tt;
			char temp[5];
			for(int i=0;i<4&&!success;i++)
			{
				sprintf(temp,"%d",t);
				for(int j=i==0?1:0;j<10&&!success;j++)
				{
					temp[i]=j+'0';
					sscanf(temp,"%d",&tt);
					if(tt==ed)
						success=1;
					if(!noprime[tt]&&step[tt]==-1)
					{
						Q.push(tt);
						step[tt]=step[t]+1;
					}
				}
			}
		}
		printf("%d\n",step[ed]);
	}
	return 0;
}
