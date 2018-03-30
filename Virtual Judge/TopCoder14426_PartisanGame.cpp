#include<iostream>
#include<vector>
#include<string>
using namespace std;

class PartisanGame
{
	int step[(1<<10)+10];
public:
	string getWinner(int n,vector<int> &a,vector<int> &b)
	{
		if(n==0)
			return "Bob";
		int ga=0,gb=0;
		for(vector<int>::iterator i=a.begin();i!=a.end();i++)
			ga^=1<<(*i-1);
		for(vector<int>::iterator i=b.begin();i!=b.end();i++)
			gb^=1<<(*i-1);
		fill(step,step+(1<<10),-1);
		int da=1,db=1;
		step[(da<<5)|db]=0;
		for(register int i=1,s;i<=n;i++)
		{
			da<<=1,db<<=1,da|=(ga&(db>>1))==0,db|=(gb&(da>>1))==0;
			s=((da&31)<<5)|(db&31);
			if(step[s]!=-1)
				i+=((n-i)/(i-step[s]))*(i-step[s]);
			else
				step[s]=i;
		}
		if(da&1)
			return "Bob";
		return "Alice";
	}
};

vector<int> a,b;
PartisanGame PG;
int main()
{
	int n,na,nb;
	cin>>n>>na>>nb;
	for(int i=1,x;i<=na;i++)
	{
		cin>>x;
		a.push_back(x);
	}
	for(int i=1,x;i<=nb;i++)
	{
		cin>>x;
		b.push_back(x);
	}
	cout<<PG.getWinner(n,a,b)<<endl;
	return 0;
}
