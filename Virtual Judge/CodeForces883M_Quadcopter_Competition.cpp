#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
	int x1,y1,x2,y2;
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	if(x1==x2)x1++;
	if(y1==y2)y1++;
	printf("%d\n",(abs(x1-x2)+abs(y1-y2)+2)*2);
	return 0;
}
