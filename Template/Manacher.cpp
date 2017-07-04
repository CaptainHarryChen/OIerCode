#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
#define MAXN 110005
char str[MAXN];
namespace Manacher
{
	char temp[MAXN<<1];
	int P[MAXN<<1];
	void Manacher(const char *str)
	{
		int n=strlen(str);
		temp[0]='@';
		for(int i=0;i<n;i++)
			temp[i*2+1]='#',temp[i*2+2]=str[i];
		temp[n*2+1]='#';temp[n*2+2]='$';
		int mx=0,po;
		for(int i=1;i<=n*2+1;i++)
		{
			if(mx>i)
				P[i]=min(mx-i,P[2*po-i]);
			else
				P[i]=1;
			while(temp[i-P[i]]==temp[i+P[i]])
				P[i]++;
			if(P[i]+i>mx)
			{mx=P[i]+i;po=i;}
		}
	}
}
int main()
{
	freopen("Manacher_data.in","r",stdin);
	int ans,n;
	while(~scanf("%s",str))
	{
		Manacher::Manacher(str);
		n=strlen(str);
		ans=0;
		for(int i=1;i<=2*n+1;i++)
			ans=max(ans,Manacher::P[i]-1);
		printf("%d\n",ans);
	}
	return 0;
}
