#include<iostream>
#include<cstdio>
#include<cstring>
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
    char e[3],s[11]={0};
    for(int i=0;i<m;i++)
    {
        scanf("%s%s",e,s);
        if(e[0]=='I')
        {
            t=new stu;
            strcpy(t->name,s);
            t->next=head;
            head=t;
            n++;
        }
        else
            for(p=head;p!=NULL;p=p->next)
            {
                if(strcmp(p->name,s)==0)
				{
					if(p==head){head=p->next;q=p;}
                    else q->next=p->next;
				}
				else
					q=p;
            }
    }
    for(p=head;p!=NULL;p=p->next)
        printf("%s\n",p->name);
    return 0;
}
