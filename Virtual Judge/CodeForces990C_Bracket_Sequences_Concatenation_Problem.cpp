#include<iostream>
#include<string>
using namespace std;
const int MAXN=300005;

int n;
string str[MAXN];
int l[MAXN],r[MAXN];
int cnt[MAXN];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>str[i];
		int sum=0;
		for(int j=0;j<(int)str[i].size();j++)
		{
			if(str[i][j]==')')sum++;
			else sum--;
			l[i]=max(l[i],sum);
		}
		sum=0;
		for(int j=(int)str[i].size()-1;j>=0;j--)
		{
			if(str[i][j]=='(')sum++;
			else sum--;
			r[i]=max(r[i],sum);
		}
		if(r[i]==0)
			cnt[l[i]]++;
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
		if(l[i]==0)
			ans+=cnt[r[i]];
	cout<<ans<<endl;
	
	return 0;
}
