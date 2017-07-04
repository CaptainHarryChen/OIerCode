#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int dis[5005];
struct dian
{
	int id,v;
	dian*next;
	dian(){id=v=0;next=NULL;}
}arr[5005];
queue<dian>q;
int main()
{
	int n,m,a,b,c;
	cin>>n>>m;
	for(int i=0;i<n;i++)arr[i].id=i+1;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		dian*p=new dian;
		p->next=arr[a-1].next;
		arr[a-1].next=p;
		p->id=b;
		p->v=c;
	}
	memset(dis,127,sizeof(dis));
	dis[0]=0;
	q.push(arr[0]);
	while(!q.empty())
	{
		dian t=q.front();
		for(dian*p=t.next;p!=NULL;p=p->next)
			if(dis[p->id-1]>dis[t.id-1]+p->v)
			{
				dis[p->id-1]=dis[t.id-1]+p->v;
				q.push(arr[p->id-1]);
			}
		q.pop();
	}
	printf("%d\n",dis[n-1]);
	return 0;
}
