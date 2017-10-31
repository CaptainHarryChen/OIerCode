#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN=405;
int n;
string s[MAXN];
bool has[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		int l=s[i].length();
		for(int j=0;j<l;j++)
		{
			if(s[i][j]=='u')
			{
				s[i]=s[i].substr(0,j)+string("oo")+s[i].substr(j+1,l-j-1);
				l++;
			}
			if(j<l-1&&s[i][j]=='k'&&s[i][j+1]=='h')
			{
				s[i]=s[i].substr(0,j)+string("h")+s[i].substr(j+2,l-j-2);
				l--;
				j-=2;
				if(j<-1)
					j=-1;
			}
		}
	}
	int ans=n;
	for(int i=1;i<=n;i++)
		if(!has[i])
			for(int j=i+1;j<=n;j++)
				if(!has[i]&&s[i]==s[j])
				{
					has[j]=1;
					ans--;
				}
	printf("%d\n",ans);
	return 0;
}
