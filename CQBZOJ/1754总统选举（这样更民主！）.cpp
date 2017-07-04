#include<cstdio>
int main()
{
	char c[2];
	int cnt[4]={0};
	while(~scanf("%s",c))
		cnt[c[0]-'A']++;
	int maxn=-1,k;
	for(int i=0;i<3;i++)
	{
		if(maxn<cnt[i])
		{maxn=cnt[i];k=i;}
	}
	for(int i=0;i<3;i++)
		if(i!=k&&cnt[i]==maxn)
		{printf("no result\n");return 0;}
	printf("%d\n",k+1);
	return 0;
}
