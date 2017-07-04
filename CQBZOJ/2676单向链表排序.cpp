#include<iostream>
#include<cstdio>
#include<list>
using namespace std;
list<int>a;
int main()
{
    int n,x;
    scanf("%d",&n);
    for(int i=0;i<n+1;i++)
	{
		scanf("%d",&x);
		a.push_back(x);
	}
    a.sort();
	list<int>::iterator p=a.begin();
	printf("%d",*p);
	p++;
    for(;p!=a.end();p++)
		printf(" %d",*p);
	printf("\n");
    return 0;
}
 