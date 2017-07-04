#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXM 1005
struct IP
{
	unsigned char n[4];
}ip[MAXM],a,b;
bool cmp(IP a,IP b)
{
	for(int i=0;i<4;i++)
		if(a.n[0]<b.n[0])
			return 1;
		else if(a.n[0]>b.n[0])
			return 0;
	return 0;
}
int m;
int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d.%d.%d.%d",&ip[i].n[0],&ip[i].n[1],&ip[i].n[2],&ip[i].n[3]);
	sort(ip+1,ip+m+1,cmp);
	bool flag=1;
	for(int i=0;i<4;i++)
	{
		for(int j=(1<<7);j;j=(j>>1))
		{
			for(int k=2;k<=m;k++)
				if((ip[k].n[i]&j)!=(ip[1].n[i]&j))
				{flag=0;break;}
			if(!flag)
				break;
			b.n[i]+=j;
			a.n[i]+=(ip[1].n[i]&j);
		}
		if(!flag)
			break;
	}
	printf("%d.%d.%d.%d\n",a.n[0],a.n[1],a.n[2],a.n[3]);
	printf("%d.%d.%d.%d\n",b.n[0],b.n[1],b.n[2],b.n[3]);
	return 0;
}
