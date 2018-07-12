#include<iostream>
#include<string>
using namespace std;

string s;

int main()
{
	int m;
	cin>>s>>m;
	int len=s.length();
	int l,r,k;
	while(m--)
	{
		cin>>l>>r>>k;
		k%=(r-l+1);
		s=s.substr(0,l-1)+s.substr(r-k,k)+s.substr(l-1,(r-l+1)-k)+s.substr(r,len-r);
	}
	cout<<s<<endl;
	
	return 0;
}
