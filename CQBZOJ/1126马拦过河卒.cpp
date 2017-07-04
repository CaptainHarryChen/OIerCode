#include<cstdio>
#include<iostream>
using namespace std;
int f[100][100];
int main()
{
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	for(int i=0;i<=n;i++)f[i][0]=1;
	for(int i=0;i<=m;i++)f[0][i]=1;
	f[a][b]=-1;
	for(int i=a-2>=0?a-2:0;i<=(a+2<=n?a+2:0);i++)
		for(int j=b-2>=0?b-2:0;j<=(b+2<=m?b+2:0);j++)
			if((i-a)*(i-a)+(j-b)*(j-b)==5)
				f[i][j]=-1;
	if(f[1][0]==-1&&f[0][1]==-1){cout<<0<<endl;return 0;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(f[i][j]==-1)
				continue;
			f[i][j]=(f[i-1][j]==-1?0:f[i-1][j])+(f[i][j-1]==-1?0:f[i][j-1]);
		}
	cout<<f[n][m]<<endl;
	return 0;
}
