#include<iostream>
#include<cstdio>
#include<list>
using namespace std;
list<int>monkey;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        monkey.push_back(i);
	list<int>::iterator p=monkey.begin();
    for(int i=n,j=1;i!=1;)
	{
		if(j==m)
		{
			p=monkey.erase(p);
			if(p==monkey.end())p=monkey.begin();
			j=1;
			i--;
		}
		else
		{j++;p++;if(p==monkey.end())p=monkey.begin();}
	}
    printf("%d\n",*monkey.begin());
    return 0;
}
