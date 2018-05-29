#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
const int MAXN=10000005;

unsigned long long seed;
inline long double gen()
{
	static const long double Z = ( long double )1.0 / (1LL<<32);
	seed >>= 16;
	seed &= ( 1ULL << 32 ) - 1;
	seed *= seed;
	return seed * Z;
}

long double a[MAXN];

int main()
{
	int N,n;
	long double m,ans;
	cin>>N;
	for(int c=1;c<=N;c++)
	{
		cin>>n>>seed;
		m=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=gen();
			m+=a[i]/n;
		}
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=(a[i]-m)*(a[i]-m)/n;
		ans=sqrt(ans);
		cout<<"Case #"<<c<<": "<<fixed<<setprecision(5)<<ans<<endl;
	}
	
	return 0;
}
