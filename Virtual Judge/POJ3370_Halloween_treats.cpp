#include<cstdio>
#include<cstring>
const int MAXN=100005;
int a[MAXN];
int flag[MAXN];
int main()
{
	int c,n;
	while(scanf("%d%d",&c,&n)!=EOF)
	{
		if(c==0&&n==0)
			break;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]+=a[i-1];
			a[i]%=c;
		}
		memset(flag,-1,sizeof flag);
		flag[0]=0;
		for(int i=1;i<=n;i++)
			if(flag[a[i]]!=-1)
			{
				for(int j=flag[a[i]]+1;j<i;j++)
					printf("%d ",j);
				printf("%d\n",i);
				break;
			}
			else
				flag[a[i]]=i;
	}
		
	return 0;
}
