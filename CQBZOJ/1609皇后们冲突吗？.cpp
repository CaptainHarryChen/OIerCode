#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
char a[10][10];
bool f(int i,int j)
{
	for(int k=i-1;k>=0;k--)
		if(a[k][j]=='Q')
			return 0;
	for(int k=i+1;k<8;k++)
		if(a[k][j]=='Q')
			return 0;
	for(int k=j-1;k>=0;k--)
		if(a[i][k]=='Q')
			return 0;
	for(int k=j+1;k<8;k++)
		if(a[i][k]=='Q')
			return 0;
	for(int k=1;i+k<8&&j+k<8;k++)
		if(a[i+k][j+k]=='Q')
			return 0;
	for(int k=1;i+k<8&&j-k>=0;k++)
		if(a[i+k][j-k]=='Q')
			return 0;
	for(int k=1;i-k>=0&&j-k>=0;k++)
		if(a[i-k][j-k]=='Q')
			return 0;
	for(int k=1;i-k>=0&&j+k<8;k++)
		if(a[i-k][j+k]=='Q')
			return 0;
	return 1;
}
int main()
{
	for(int i=0;i<8;i++)
		scanf("%s",a[i]);
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(a[i][j]=='Q')
				if(!f(i,j)){cout<<"YES"<<endl;return 0;}
	cout<<"NO"<<endl;
	return 0;
}
