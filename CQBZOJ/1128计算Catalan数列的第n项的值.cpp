#include<cstdio>
long long n,c[35]={0,0,1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452, 18441865660680,70079089510584,263747951750360};
int main()
{
	scanf("%lld",&n);
	printf("%lld\n",c[n]);
	return 0;
}
