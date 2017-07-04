#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,dig[15],ans;
int main()
{
	int T;
	scanf("%d\n",&T);
	int temp=-1;
	while(T--)
	{
		if(temp!=-1)
			dig[1]=temp;
		else
			scanf("%d",dig+1);
		for(int i=2;;i++)
		{
			if(scanf("%d",dig+i)!=1)
			{n=i-1;break;}
			if(dig[i]<=dig[i-1])
			{temp=dig[i];n=i-1;break;}
		}
		ans=0x7FFFFFFF;
		sort(dig+1,dig+n+1);
		do
		{
			int len=n/2;
			if((dig[1]==0&&len>1)||(dig[len+1]==0&&n-len>1))
				continue;
			int x=0,y=0;
			for(int i=1;i<=len;i++)
				x=x*10+dig[i];
			for(int i=len+1;i<=n;i++)
				y=y*10+dig[i];
			ans=min(ans,abs(x-y));
		}while(next_permutation(dig+1,dig+n+1));
		printf("%d\n",ans);
	}
	return 0;
}
