#include<cstdio>
#include<cstring>
const int MAXN=1000000;
bool unhappy[15][MAXN];
bool check_mark(int x,int base,bool mode)
{
	if(x==1)
		return 1;
	if(x<MAXN&&unhappy[base][x])
		return 0;
	if(x<MAXN&&mode&&!unhappy[base][x])
		return 1;
	if(x<MAXN)
		unhappy[base][x]=1;
	int bit=1;
	while(bit*base<=x)
		bit*=base;
	char num[100];
	int tx=x,dig=0;
	while(tx)
	{
		num[dig]=tx/bit;
		tx%=bit;
		dig++;
		bit/=base;
	}
	int sum=0;
	for(int i=0;i<dig;i++)
		sum+=num[i]*num[i];
	if(check_mark(sum,base,mode))
	{
		if(x<MAXN)
			unhappy[base][x]=0;
		return 1;
	}
	if(x<MAXN)
		unhappy[base][x]=1;
	return 0;
}
void Init()
{
	for(int base=2;base<=10;base++)
		for(int j=2;j<MAXN;j++)
			check_mark(j,base,0);
}
int main()
{
	Init();
	int T,x,req[10],n;
	char ch;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		ch=0;n=0;
		for(n=0;ch!='\n'&&ch!='\r';n++)
		{
			scanf("%d",&x);
			req[n]=x;
			scanf("%c",&ch);
		}
		bool success=0;
		for(int i=2;!success;i++)
		{
			success=1;
			for(int j=0;j<n;j++)
				if(!check_mark(i,req[j],1))
				{
					success=0;
					break;
				}
			if(success)
				printf("Case #%d: %d\n",Case,i);
		}
	}
	return 0;
}
