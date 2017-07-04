#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int f[45][45][45][45],n,m,arr[1000],a,b,c,d;
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(int i=0,x;i<m;i++)
	{
		scanf("%d",&x);
		switch(x)
		{
			case 1:a++;break;
			case 2:b++;break;
			case 3:c++;break;
			case 4:d++;break;
		}
	}
	for(int x1=0;x1<=a;x1++)
		for(int x2=0;x2<=b;x2++)
			for(int x3=0;x3<=c;x3++)
				for(int x4=0;x4<=d;x4++)
				{
					int max=0;
					if(x1!=0&&f[x1-1][x2][x3][x4]>max)
						max=f[x1-1][x2][x3][x4];
					if(x2!=0&&f[x1][x2-1][x3][x4]>max)
						max=f[x1][x2-1][x3][x4];
					if(x3!=0&&f[x1][x2][x3-1][x4]>max)
						max=f[x1][x2][x3-1][x4];
					if(x4!=0&&f[x1][x2][x3][x4-1]>max)
						max=f[x1][x2][x3][x4-1];
					f[x1][x2][x3][x4]=max+arr[x1+2*x2+3*x3+4*x4];
				}
	printf("%d\n",f[a][b][c][d]);
	return 0;
}
