#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100005
int str[MAXN];
namespace Manacher
{
	int temp[MAXN<<1];
	int P[MAXN<<1];
	void manacher(const int *str,int n)
	{
		temp[0]=-1;
		for(int i=0;i<n;i++)
			temp[i*2+1]=-3,temp[i*2+2]=str[i];
		temp[n*2+1]=-3;temp[n*2+2]=-2;
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
	int n,test,ans;
	scanf("%d",&test);
	using namespace Manacher;
	for(int tt=1;tt<=test;tt++)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d",&str[i]);
		manacher(str,n);
		n=n*2+1;
		printf("Case #%d: ",tt);
		ans=1;
		for(int i=1;i<=n;i+=2)
			for(int j=ans;j<=P[i];j+=2)
				if(P[i+j-1]>=j)
					ans=j;
		printf("%d\n",ans/2*3);
	}
	return 0;
}
