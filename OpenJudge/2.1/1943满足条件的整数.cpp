#include<cstdio>
#include<cmath>
int main()
{
	for(int i=2;i<=100;i++)
		for(int j=i;j<=100;j++)
		{
			int s=sqrt(i*i+j*j);
			if(s<=100&&s*s==i*i+j*j)
				printf("%d*%d + %d*%d = %d*%d\n",i,i,j,j,s,s);
		}
	return 0;
}
