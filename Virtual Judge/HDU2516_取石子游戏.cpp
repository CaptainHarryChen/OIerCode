#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> fib;

int main()
{
	fib.push_back(1);
	fib.push_back(1);
	for(int i=1;;i++)
	{
		int t=fib[i]+fib[i-1];
		if(t<0)break;
		fib.push_back(t);
	}
	
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		if(*lower_bound(fib.begin(),fib.end(),n)==n)
			puts("Second win");
		else
			puts("First win");
	}
	return 0;
}
