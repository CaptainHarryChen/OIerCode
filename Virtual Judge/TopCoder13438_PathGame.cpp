#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
const int MAXN=1030;

class PathGame {
public:
	string judge(vector<string>&);
};

int sg[MAXN][4];
bool vis[MAXN];
int DP(int x,int t)
{
	if(t==0)
		vis[sg[x-1][0]]=true;
	else if(t==1)
		vis[sg[x-1][1]]=true;
	else if(t==2)
		vis[sg[x-1][2]]=vis[sg[x-1][1]]=vis[sg[x-1][0]]=true;
	else
		vis[sg[x-1][2]]=true;
	for(int i=2;i<x;i++)
	{
		if(t==0)
		{
			vis[sg[i-1][1]^sg[x-i][1]]=true;
			vis[sg[i-1][0]^sg[x-i][0]]=true;
		}
		else if(t==1)
		{
			vis[sg[i-1][1]^sg[x-i][0]]=true;
			vis[sg[i-1][0]^sg[x-i][1]]=true;
		}
		else if(t==2)
		{
			vis[sg[i-1][2]^sg[x-i][0]]=true;
			vis[sg[i-1][2]^sg[x-i][1]]=true;
		}
		else
			vis[sg[i-1][2]^sg[x-i][2]]=true;
	}
	for(int i=0;i<MAXN;i++)
		if(!vis[i])
		{
			sg[x][t]=i;
			return i;
		}
	return -1;
}
string PathGame::judge(vector<string> &board)
{
	fill(sg[0],sg[0]+MAXN,-1);
	fill(sg[1],sg[1]+MAXN,-1);
	int ans=0,last=-1,n=board[0].size();
	sg[0][0]=sg[0][1]=sg[0][2]=sg[0][3]=0;
	sg[1][0]=sg[1][2]=sg[1][3]=1;sg[1][1]=0;
	for(int i=2;i<=n;i++)
		for(int t=0;t<4;t++)
		{
			fill(vis,vis+MAXN,0);
			DP(i,t);
		}
	/*
	for(int i=1;i<=n;i++)
		cerr<<"sg["<<i<<"]:"<<sg[i][0]<<' '<<sg[i][1]<<' '<<sg[i][2]<<' '<<sg[i][3]<<endl;
	*/
	for(int i=0;i<n;i++)
		if(board[0][i]=='#'||board[1][i]=='#')
		{
			if(last==-1)
				ans^=sg[i-last-1][2];
			else
				ans^=sg[i-last-1][(board[0][last]=='#')!=(board[0][i]=='#')];
			last=i;
		}
	if(last==-1)
		ans^=sg[n-1-last][3];
	else
		ans^=sg[n-1-last][2];
	if(ans)
		return "Snuke";
	return "Sothe";
}

PathGame PG;
vector<string> b;
string s;
int main()
{
	cin>>s;
	b.push_back(s);
	cin>>s;
	b.push_back(s);
	cout<<PG.judge(b)<<endl;
	return 0;
}
