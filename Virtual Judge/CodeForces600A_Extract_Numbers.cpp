#include<iostream>
#include<string>
#include<vector>
using namespace std;

string S;
vector<string> num,oth;

bool check(const string &s)
{
	if(s.size()==0)
		return false;
	for(int i=0;i<(int)s.size();i++)
		if(!(s[i]>='0'&&s[i]<='9'))
			return false;
	if(s[0]=='0'&&s.size()==1)
		return true;
	else if(s[0]=='0')
		return false;
	return true;
}

int main()
{
	cin>>S;
	int last=0;
	for(int i=0;i<=(int)S.size();i++)
		if(S[i]==';'||S[i]==','||i==(int)S.size())
		{
			string tmp=S.substr(last,i-last);
			last=i+1;
			if(check(tmp))
				num.push_back(tmp);
			else
				oth.push_back(tmp);
		}
	if(num.size())
	{
		cout<<'\"';
		for(int i=0;i<(int)num.size();i++)
			cout<<num[i]<<((i==(int)num.size()-1)?"":",");
		cout<<'\"'<<endl;
	}
	else
		cout<<'-'<<endl;
	if(oth.size())
	{
		cout<<'\"';
		for(int i=0;i<(int)oth.size();i++)
			cout<<oth[i]<<((i==(int)oth.size()-1)?"":",");
		cout<<'\"'<<endl;
	}
	else
		cout<<'-'<<endl;
	
	return 0;
}
