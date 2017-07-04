#include<iostream>
#include<cstdio>
using namespace std;
struct stu
{
    char name[11],e[3];
    int i;
    double x,y;
	stu *next;
}*head,*p;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        p=new stu;
		scanf("%s%d%lf%lf%s",p->name,&p->i,&p->x,&p->y,p->e);
		p->next=head;
		head=p;
	}
	for(p=head;p!=NULL;p=p->next)
		printf("%s:id(%d) day1(%.1lf) day2(%.1lf) grade(%c)\n",p->name,p->i,p->x,p->y,p->e[0]);
    return 0;
}