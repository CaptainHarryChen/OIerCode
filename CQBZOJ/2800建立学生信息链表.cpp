#include<iostream>
#include<cstdio>
#include<list>
#include<cstring>
using namespace std;
struct stu
{
    char name[11];
    int i;
    stu *next;
	stu(){}
	stu(char m[],int y)
	{
		strcpy(name,m);
		i=y;
	}
};
list<stu>a;
int main()
{
    int n,y;
	char m[11];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
	{
		scanf("%s%d",m,&y);
		a.push_back(stu(m,y));
	}
    for(list<stu>::iterator p=a.begin();p!=a.end();p++)
        printf("%s %d\n",p->name,p->i);
    return 0;
}
