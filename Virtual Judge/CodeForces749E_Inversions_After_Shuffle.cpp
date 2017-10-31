#include<iostream>
#include<iomanip>
using namespace std;
const int MAXN=100005;
struct BIT
{
	long long sum[MAXN];
	void insert(int x,long long val)
	{
		while(x<MAXN)
		{
			sum[x]+=val;
			x+=(x&(-x));
		}
	}
	long long get(int x)
	{
		long long ret=0;
		while(x)
		{
			ret+=sum[x];
			x-=(x&(-x));
		}
		return ret;
	}
};
int n;
int A[MAXN];
BIT trev,trsum;
long long rev[MAXN],rsum[MAXN];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>A[i];
	for(int i=n;i>=1;i--)
	{
		rev[i]=trev.get(A[i]);
		rsum[i]=trsum.get(A[i]);
		trev.insert(A[i],1);
		trsum.insert(A[i],i);
	}
	long double ans=0.0L;
	ans+=1.0L*(n-1)/24.0L*(n+2);
	for(int i=1;i<=n;i++)
		ans+=1.0L*rev[i]*((1.0L*n*n+n)-(2.0L*i+2.0L*n*i))/n/(n+1)+2.0L*i*rsum[i]/n/(n+1);
	cout<<fixed<<setprecision(30)<<ans<<endl;
	return 0;
}

