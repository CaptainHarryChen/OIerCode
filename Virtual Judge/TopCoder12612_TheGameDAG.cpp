#include<iostream>
#include<vector>
using namespace std;
const int MAXN=12;

class TheGameDAG {
public:
	double getProbability(vector<int>&,int,int);
};

int n;
double p,q;
int A,B;
vector<int> P;
int req[MAXN];

void dfs(int u)
{
	if(u==n)
	{
		double prob=1,a=1,b=1;
		for(int i=0;i<n;i++)
		{
			int cnt=1;
			for(int j=i+1;j<n;j++)
				if(req[j]<i)
					cnt++;
			prob*=1.0/cnt;
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<req[i];j++)
				b*=2.0;
		a=b;
		if(req[B]>A)
			a/=2.0;
		else if(req[B]<A)
			a=0;
		p+=a*prob;
		q+=b*prob;
		return;
	}
	for(req[u]=-1;req[u]<u;req[u]++)
		dfs(u+1);
}

double TheGameDAG::getProbability(vector<int> &P,int A,int B)
{
	n=P.size();
	::P=P;
	for(::A=0;P[::A]!=A;::A++);
	for(::B=0;P[::B]!=B;::B++);
	dfs(0);
	return p/q;
}

vector<int>a;
TheGameDAG TGD;
int main()
{
	int n,u,v;
	cin>>n;
	for(int i=0,x;i<n;i++)
	{
		cin>>x;
		a.push_back(x);
	}
	cin>>u>>v;
	cout<<TGD.getProbability(a,u,v)<<endl;
	return 0;
}
