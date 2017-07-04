#include<iostream>
#include<cstring>
#define MAXN 25
using namespace std;
struct State
{
	int v[3];
};
bool ans[MAXN],vis[MAXN][MAXN];
State cap,start;
void dfs(State t)
{
	if(t.v[0]==0)ans[t.v[2]]=1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(i!=j)
			{
				if(t.v[i]==0||t.v[j]==cap.v[j])
					continue;
				int amount=min(cap.v[j],t.v[i]+t.v[j])-t.v[j];
				State tt=t;
				tt.v[i]-=amount;
				tt.v[j]+=amount;
				if(!vis[tt.v[0]][tt.v[1]])
				{
					vis[tt.v[0]][tt.v[1]]=1;
					dfs(tt);
				}
			}
}
int main()
{
	int a,b,c;
	cin>>a>>b>>c;
	cap.v[0]=a;cap.v[1]=b;cap.v[2]=c;
	start.v[0]=0;start.v[1]=0;start.v[2]=c;
	vis[start.v[0]][start.v[1]]=1;
	dfs(start);
	int print[MAXN],p=0;
	for(int i=0;i<=c;i++)
		if(ans[i])
			print[p++]=i;
	for(int i=0;i<p-1;i++)
		cout<<print[i]<<' ';
	cout<<print[p-1]<<endl;
	return 0;
}
