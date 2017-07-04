#include<iostream>
#include<cstdio>
using namespace std;
int x,y;
int extend_Eulid(long long a,long long b)
{
    if(b==0)
	{
		x=1;y=0;
		return a;
    }
    int ans=extend_Eulid(b,a%b);
    long long temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
int main()
{
    int a,b;
    cin>>a>>b;
    extend_Eulid(a,b);
	x=x%b;
	while(x<0)x+=b;
	printf("%d\n",x);
    //printf("%d=(%d)*%d+(%d)*%d\n",q,x,a,y,b);
    return 0;
}
