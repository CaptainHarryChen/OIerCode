#include<iostream>
#include<cstdio>
using namespace std;
struct ball
{
	int id;
    ball*next,*last;
}*p,*head,*a[100005];
int main()
{
    int n,m,s,t;
    char e[3];
    scanf("%d%d",&n,&m);
	p=new ball;
    for(int i=0;i<n;i++)
    {
        p->next=new ball;
		p->id=i+1;
		a[i]=p;
        if(i==0){head=p;p->last=NULL;p->next->last=p;}
		else if(i==n-1) p->next=NULL;
		else p->next->last=p;
        p=p->next;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s%d%d",e,&s,&t);
		if(a[s-1]==head){head=a[s-1]->next;head->last=NULL;}
		else if(a[s-1]->next==NULL){a[s-1]->last->next=NULL;}
		else{a[s-1]->last->next=a[s-1]->next;a[s-1]->next->last=a[s-1]->last;}
		if(e[0]=='A')
		{
			if(a[t-1]==head){head=a[s-1];head->last=NULL;}
			else{a[s-1]->last=a[t-1]->last;a[t-1]->last->next=a[s-1];}
			a[s-1]->next=a[t-1];
			a[t-1]->last=a[s-1];
		}
		else
		{
			if(a[t-1]->next==NULL){a[t-1]->next=a[s-1];a[s-1]->last=a[t-1];a[s-1]->next=NULL;}
			else{a[s-1]->next=a[t-1]->next;a[t-1]->next->last=a[s-1];}
			a[t-1]->next=a[s-1];
			a[s-1]->last=a[t-1];
		}
	}
	for(p=head;p!=NULL;p=p->next)
		printf("%d\n",p->id);
    return 0;
}
