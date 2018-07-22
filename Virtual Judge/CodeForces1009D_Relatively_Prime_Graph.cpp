#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=100005;

vector< pair<int,int> > edge;

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	if(m<n-1)
	{
		puts("Impossible");
		return 0;
	}
	for(int i=1;i<=n&&m;i++)
	{
		for(int j=i+1;j<=i+i&&j<=n&&m;j++)
			if(gcd(i,j)==1)
				for(int k=j;k<=n&&m;k+=i)
					edge.push_back(make_pair(i,k)),m--;
	}
	if(m==0)
	{
		puts("Possible");
		for(vector< pair<int,int> >::iterator it=edge.begin();it!=edge.end();it++)
			printf("%d %d\n",it->first,it->second);
	}
	else
		puts("Impossible");
	return 0;
}
