#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 100005
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
int n,m;
bool f[MAXN];
char s[MAXN][20];
int main()
{
	Read(n);Read(m);
	for(int i=0;i<n;i++)
	{
		Read(f[i]);
		scanf("%s",s[i]);
	}
	int ans=0;
	for(int i=1,a,b,c;i<=m;i++)
	{
		Read(a),Read(b);
		if(a!=f[ans])
			c=1;
		else
			c=-1;
		ans=ans+c*b;
		while(ans<0)ans+=n;
		while(ans>=n)ans-=n;
	}
	printf("%s\n",s[ans]);
	return 0;
}
