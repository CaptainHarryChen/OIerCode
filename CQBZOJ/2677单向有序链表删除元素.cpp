#include<iostream>
#include<cstdio>
#include<list>
using namespace std;
list<int>a;
int main()
{
    int n,x,f=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		a.push_back(x);
	}
	list<int>::iterator p=a.begin();
	scanf("%d",&x);
	for(;p!=a.end();p++)if(*p==x){f=1;break;}
	if(f)
		a.remove(x);
	else
	{
		a.push_back(x);
    a.sort();
	}
	p=a.begin();
	printf("%d",*p);
	p++;
    for(;p!=a.end();p++)
		printf(" %d",*p);
	printf("\n");
    return 0;
}
