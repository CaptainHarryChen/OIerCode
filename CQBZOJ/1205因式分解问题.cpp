#include<cstdio>
#include<iostream>
using namespace std;
int n,f[10000000];
int ff(int b)
{
	if(b<10000000&&f[b])return f[b];
	int sum=1;
    for(int i=2;i*i<=b;i++)
    {
        if(b%i==0)
        {
			sum+=ff(i);
			if(i*i!=b)sum+=ff(b/i);
        }
    }
    if(b<10000000)f[b]=sum;
	return sum;
}
int main()
{
    scanf("%d",&n);
	f[1]=1;
    printf("%d\n",ff(n));
    return 0;
}
