#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXST=(1<<20)+10;
int step[2][MAXST];
typedef pair<int,bool>state;
queue<state>Q;
int main()
{
	memset(step,-1,sizeof step);
	int st=0,ed=0;
	for(int i=0,x,bit=1;i<20;i++)
	{
		scanf("%d",&x);
		if(x)
			st+=bit;
		bit<<=1;
	}
	if(st==ed)
	{
		printf("0\n");
		return 0;
	}
	step[0][st]=0;
	step[1][ed]=0;
	Q.push(make_pair(st,0));
	Q.push(make_pair(ed,1));
	while(!Q.empty())
	{
		state t=Q.front();
		Q.pop();
		for(int i=0,bit=1;i<20;i++,bit<<=1)
		{
			int tt=t.first;
			tt^=bit;
			if(i>0)
				tt^=(bit>>1);
			if(i<20-1)
				tt^=(bit<<1);
			if(step[t.second][tt]!=-1)
				continue;
			step[t.second][tt]=step[t.second][t.first]+1;
			if(step[t.second^1][tt]!=-1)
			{
				printf("%d\n",step[t.second][tt]+step[t.second^1][tt]);
				return 0;
			}
			Q.push(make_pair(tt,t.second));
		}
	}
	return 0;
}
