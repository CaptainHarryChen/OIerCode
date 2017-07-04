#include<cstdio>
#include<cstring>
int main()
{
	bool f[1005];
	int num[20];
	while(1)
	{
		memset(f,0,sizeof f);
		memset(num,0,sizeof num);
		int i=0;
		do
		{
			i++;
			scanf("%d",&num[i]);
			f[num[i]]=1;
			if(num[i]==-1)return 0;
		}while(num[i]!=0);
		int cnt=0;
		for(i=1;num[i];i++)
			cnt+=f[num[i]*2];
		printf("%d\n",cnt);
	}
	return 0;
}
