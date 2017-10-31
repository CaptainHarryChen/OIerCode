#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a,b;
	cin>>a>>b;
	int t,cur=0,ans=0,len=b.length();
	while(t=a.find(b,cur),t!=-1)
	{
		a[t+len-1]='#';
		cur=t+len;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
