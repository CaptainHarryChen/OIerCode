#include<string>
#include<iostream>
using namespace std;
string a,b;
string op(string s)
{
	int l=s.length();
	if(l%2==0)
	{
		int mid=l/2;
		string sl=op(s.substr(0,mid));
		string sr=op(s.substr(mid,l-mid));
		if(sl>sr)
			return sr+sl;
		else
			return sl+sr;
	}
	return s;
}
int main()
{
	cin>>a>>b;
	a=op(a);
	b=op(b);
	if(a==b)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
