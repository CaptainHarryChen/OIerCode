#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
const int MAXN=1005;

class GameOfSegments {
public:
	int winner(int);
};

int sg[MAXN];
int DP(int x)
{
	if(sg[x]!=-1)
		return sg[x];
	bool vis[MAXN]={0};
	for(int i=0;i<=x-2-i;i++)
		vis[DP(i)^DP(x-2-i)]=true;
	for(int i=0;i<1024;i++)
		if(!vis[i])
		{
			sg[x]=i;
			return i;
		}
	return -1;
}
int GameOfSegments::winner(int N)
{
	fill(sg,sg+MAXN,-1);
	sg[0]=0;
	if(DP(N))
		return 1;
	return 2;
}

GameOfSegments GOS;
int main()
{
	int n;
	cin>>n;
	cout<<GOS.winner(n)<<endl;
	return 0;
}
