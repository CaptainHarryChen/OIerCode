#include<cstdio>
bool solve(int a,int b)
{
	if(b==0)
		return 0;
	if(a/b!=1)
		return 1;
	return solve(b,a-b)^1;
}
int main()
{
	int a,b;
	while(1)
	{
		scanf("%d%d",&a,&b);
		if(!a&&!b)break;
		if(a<b)a^=b,b^=a,a^=b;
		if(solve(a,b))
			printf("Stan wins\n");
		else
			printf("Ollie wins\n");
	}
	return 0;
}
