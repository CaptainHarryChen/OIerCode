#include<iostream>
#include<string>
using namespace std;
int gcd(int a,int b,int &x,int &y)
{
	if(b==0LL)
	{
		x=1LL;y=0LL;
		return a;
	}
	int xx,yy,d=gcd(b,a%b,xx,yy);
	x=yy;
	y=xx-a/b*yy;
	return d;
}
bool solve(int a,int b,int c,int &x,int &y)
{
	int d;
	d=gcd(a,b,x,y);
	if(c%d)return false;
	a/=d;b/=d;c/=d;
	x*=c;y*=c;
	while(x<0)
	{x+=b;y-=a;}
	while(y<0)
	{x-=b;y+=a;}
	return true;
}
int main()
{
	int n,p,q;
	string s;
	cin>>n>>p>>q>>s;
	int x,y;
	if(!solve(p,q,n,x,y)||x<0||y<0)
		cout<<-1<<endl;
	else
	{
		cout<<x+y<<endl;
		int cur=0;
		for(int i=1;i<=x;i++,cur+=p)
			cout<<s.substr(cur,p)<<endl;
		for(int i=1;i<=y;i++,cur+=q)
			cout<<s.substr(cur,q)<<endl;
	}
	return 0;
}
