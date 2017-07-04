#include<cstdio>
#include<iostream>
using namespace std;
char s[1005][1005];
bool f[1005][1005];
int cnt,dd[4][2]={{0,1},{1,0},{0,-1},{-1,0}},n;
bool fff(int a,int b)
{
	if(a>=0&&b>=0&&a<n&&b<n)
		return 1;
	return 0;
}
void ff(int a,int b)
{
	if(s[a][b]=='.'||!fff(a,b)||f[a][b])return;
	f[a][b]=1;
	for(int i=0;i<4;i++)
		ff(a+dd[i][0],b+dd[i][1]);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%s",s[i]);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(s[i][j]=='*'&&!f[i][j])
			{
				ff(i,j);
				cnt++;
			}
		}
	}
	cout<<cnt<<endl;
	return 0;
}
