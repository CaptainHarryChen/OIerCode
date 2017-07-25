#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long MAXN=50,MAXS=(1<<20)+10,INF=0x7FFFFFFF;
const long long LLF=0x7FFFFFFFFFFFFFFFLL;
typedef pair<long long,long long> value;
long long num[MAXN];
value s1[MAXS],s2[MAXS];
long long st1,st2;
long long a_bs(long long x)
{
	if(x>0)
		return x;
	return -x;
}
void dfs(long long x,long long n,value s[],long long &t,long long sum=0LL,long long cnt=0)
{
	if(x>n)
	{
		s[t++]=value(sum,cnt);
		return;
	}
	dfs(x+1,n,s,t,sum,cnt);
	dfs(x+1,n,s,t,sum+num[x],cnt+1);
}
int main()
{
	long long n;
	while(~scanf("%lld",&n))
	{
		memset(s1,0,sizeof s1);
		memset(s2,0,sizeof s2);
		memset(num,0,sizeof num);
		st1=st2=0;
		if(!n)
			break;
		for(long long i=1;i<=n;i++)
			scanf("%lld",num+i);
		long long mid=n/2LL;
		dfs(1,mid,s1,st1);
		dfs(mid+1,n,s2,st2);
		sort(s1,s1+st1);
		sort(s2,s2+st2);
		long long i=-1,j,ans_cnt=LLF;
		long long last=-LLF,ans_sum=LLF,ss,sc;
		while(i<st1)
		{
			i++;
			if(i>=st1)
				break;
			last=s1[i].first;
			j=lower_bound(s2,s2+st2,value(-s1[i].first,0))-s2;
			if(s1[i].second+s2[j].second==0)
				j++;
			ss=a_bs(s1[i].first+s2[j].first);
			sc=s1[i].second+s2[j].second;
			if(j<st2&&(ss<ans_sum||(ss==ans_sum&&sc<ans_cnt)))
			{
				ans_cnt=sc;
				ans_sum=ss;
			}
			j--;
			if(s1[i].second+s2[j].second==0)
				j--;
			if(j<0)continue;
			ss=a_bs(s1[i].first+s2[j].first);
			sc=s1[i].second+s2[j].second;
			if(ss<ans_sum||(ss==ans_sum&&sc<ans_cnt))
			{
				ans_cnt=sc;
				ans_sum=ss;
			}
		}
		printf("%lld %lld\n",ans_sum,ans_cnt);
	}
	return 0;
}
