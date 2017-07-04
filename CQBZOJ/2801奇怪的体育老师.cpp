#include<iostream>
#include<cstdio>
using namespace std;
struct stu
{
    char name[11];
    stu *next;
}*head,*tail,*p,*q,*t;
int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        p=new stu;
        scanf("%s",p->name);
        p->next=NULL;
        if(i==0)head=tail=p;
        else
        {
            tail->next=p;
            tail=p;
        }
    }
    scanf("%d",&m);
    int k;
    char e[3];
    for(int i=0;i<m;i++)
    {
        t=new stu;
        scanf("%s%s%d",t->name,e,&k);
        t->next=NULL;
        if(k>n||(k==n&&e[0]=='a'))
        {
            tail->next=t;
            tail=t;
			n++;
            continue;
        }
        p=head;
        if(e[0]=='a')k++;
		for(int j=1;j!=k;j++,p=p->next)q=p;
        if(p==head)
        {
            t->next=p;
            head=t;
        }
		else if(q==tail)
		{
			tail->next=t;
			tail=t;
		}
        else
        {
            q->next=t;
            t->next=p;   
        }
        n++;
    }
    for(p=head;p!=NULL;p=p->next)
        printf("%s\n",p->name);
    return 0;
}
