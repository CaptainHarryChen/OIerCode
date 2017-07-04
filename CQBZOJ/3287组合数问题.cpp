#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 2000
template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}
int K,n,m;
int prime[10]={2,3,5,7,11,13,17,19};
int ans[MAXN+5][MAXN+5];
pair<int,int>kp[2];
int ap[MAXN+5][MAXN+5][2];
void solve()
{
	for(int i=0,a=0;i<8;i++)
	if(K%prime[i]==0)
	{
		kp[a].first=prime[i];
		while(K%prime[i]==0)
		{K/=prime[i];kp[a].second++;}
		a++;
	}
	for(int i=1;i<=MAXN;i++)
		for(int j=1;j<=i;j++)
		{
			ans[i][j]=ans[i-1][min(j,i-1)]+ans[i][j-1]-ans[i-1][j-1];
			int temp=(i-j+1);
			ap[i][j][0]=ap[i][j-1][0];ap[i][j][1]=ap[i][j-1][1];
			while(temp%kp[0].first==0){temp/=kp[0].first;ap[i][j][0]++;}
			while(kp[1].first&&temp%kp[1].first==0){temp/=kp[1].first;ap[i][j][1]++;}
			temp=j;
			while(temp%kp[0].first==0){temp/=kp[0].first;ap[i][j][0]--;}
			while(kp[1].first&&temp%kp[1].first==0){temp/=kp[1].first;ap[i][j][1]--;}
			int f=0;
			if(ap[i][j][0]>=kp[0].second&&ap[i][j][1]>=kp[1].second)f=1;
			ans[i][j]+=f;
		}
}
int main()
{
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	int T;
	Read(T);Read(K);
	solve();
	while(T--)
	{
		Read(n);Read(m);
		printf("%d\n",ans[n][min(n,m)]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
