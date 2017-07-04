#include<cstdio>
const int two[16]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
void solve(int x)
{
	if(x==0)return;
	if(x==1){printf("2(0)");return;}
	if(x==2){printf("2");return;}
	int i;
	for(i=15;x<two[i];i--);
	if(i==1)
		printf("2");
	else
	{
		printf("2(");
		solve(i);
		printf(")");
	}
	if(x-two[i]!=0)
		printf("+");
	solve(x-two[i]);
}
int main()
{
	int n;
	scanf("%d",&n);
	solve(n);
	printf("\n");
	return 0;
}
