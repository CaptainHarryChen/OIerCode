#include<cstdio>
#include<cstring>
#define max(a,b) (a>b?a:b)
int K,ans[505];
char N[205];
bool flag[10005];
int main()
{
	for(int i=1,num=1;;i++)
	{
		num*=2011;
		num%=10000;
		if(flag[num])
			break;
		flag[num]=1;
		ans[i]=num;
	}
	scanf("%d",&K);
	while(K--)
	{
		scanf("%s",N);
		int len=strlen(N);
		int num=0;
		for(int i=max(len-4,0);i<len;i++)
			num=num*10+N[i]-'0';
		num%=500;
		if(num==0)num=500;
		printf("%d\n",ans[num]);
	}
	return 0;
}
