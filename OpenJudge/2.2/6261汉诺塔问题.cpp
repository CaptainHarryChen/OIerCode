#include<cstdio>
void move(int x,char a,char b,char c)//a->c used b
{
	if(x==1)
		printf("%c->%d->%c\n",a,x,c);//direct take
	else
	{
		move(x-1,a,c,b);//take the top
		printf("%c->%d->%c\n",a,x,c);//take the bottom
		move(x-1,b,a,c);
	}
}
int main()
{
	int n;
	char a,b,c;
	scanf("%d %c %c %c",&n,&a,&b,&c);
	move(n,a,c,b);
	return 0;
}
