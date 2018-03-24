#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=1005;
 
int n;
long long A[MAXN];
bool keep[MAXN];
 
vector<int> ans;
 
void del(int pos)
{
	for(int i=pos;i<=n;i++)
		A[i]=A[i+1],keep[i]=keep[i+1];
	n--;
}
 
int main()
{
	scanf("%d",&n);
	bool flag=false;
	for(int i=1;i<=n;i++)
		scanf("%lld",A+i),flag|=(A[i]>0);
	if(flag==false)
	{
		int mx=-0x7FFFFFFF,pos;
		for(int i=1;i<=n;i++)
			if(mx<A[i])
				mx=A[i],pos=i;
		printf("%d\n%d\n",mx,n-1);
		for(int i=1;i<pos;i++)
			printf("1\n");
		for(int i=n-pos+1;i>=2;i--)
			printf("%d\n",i);
		return 0;
	}
	long long sum1=0,sum2=0;
	for(int i=1;i<=n;i+=2)
		if(A[i]>0)
			sum1+=A[i];
	for(int i=2;i<=n;i+=2)
		if(A[i]>0)
			sum2+=A[i];
	if(sum1>sum2)
	{
		for(int i=1;i<=n;i+=2)
			if(A[i]>0)
				keep[i]=true;
	}
	else
	{
		for(int i=2;i<=n;i+=2)
			if(A[i]>0)
				keep[i]=true;
	}
	
	while(n>1)
	{
		if(keep[1]==false)
		{
			ans.push_back(1);
			del(1);
			continue;
		}
		if(keep[n]==false)
		{
			ans.push_back(n);
			del(n);
			continue;
		}
		bool flag=false;
		for(int i=2;i<n;i++)
			if(keep[i-1]&&keep[i+1])
			{
				ans.push_back(i);
				A[i-1]+=A[i+1];
				del(i);
				del(i);
				flag=true;
				break;
			}
		if(flag)continue;
		for(int i=2;i<n;i++)
			if(!keep[i-1]&&!keep[i+1])
			{
				ans.push_back(i);
				A[i-1]+=A[i+1];
				del(i);
				del(i);
				break;
			}
	}
	printf("%lld\n",A[1]);
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
