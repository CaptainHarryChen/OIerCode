#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
map< string,vector<string> > S;
bool check(const string &a,const string &b)
{
	int l1=a.length(),l2=b.length();
	if(a==string("789")&&b==string("89"))
	{
		l1++;
		l1--;
	}
	if(l2>l1)return false;
	for(int i=1;i<=l2;i++)
		if(a[l1-i]!=b[l2-i])
			return false;
	return true;
}
int main()
{
	int n,k;
	string ent,num;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>ent>>k;
		for(int j=1;j<=k;j++)
		{
			cin>>num;
			S[ent].push_back(num);
		}
	}
	cout<<S.size()<<endl;
	for(map< string,vector<string> >::iterator it=S.begin();it!=S.end();it++)
	{
		int sz=it->second.size();
		for(int i=0;i<sz;i++)
			for(int j=i+1;j<sz;j++)
				if(i!=j&&check(it->second[i],it->second[j]))
				{
					if(j!=sz-1)swap(it->second[j],it->second[sz-1]);
					it->second.resize(--sz);
					j--;
				}
				else if(i!=j&&check(it->second[j],it->second[i]))
				{
					if(i!=sz-1)swap(it->second[i],it->second[sz-1]);
					it->second.resize(--sz);
					i--;
					break;
				}
		cout<<it->first<<' '<<sz;
		for(int i=0;i<sz;i++)
			cout<<' '<<it->second[i];
		cout<<endl;
	}
	return 0;
}
