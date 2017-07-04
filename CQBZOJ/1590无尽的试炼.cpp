#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
bool zhishu(int a)
{
	int i;
	bool f=true;
	for (i=2;i<=sqrt(a);i++)
	{
		if (a%i==0) 
		{
			f=false;
			break ;
		}
    }
	return f;
}

int main()
{
	int n,count=0,i;
	cin>>n;
	cout<<n<<'=';
	if(zhishu(n)==true){cout<<n<<endl;return 0;}
	for(i=n/2+1;i>=2;i--)
		if(n%i==0)
			if(zhishu(i)==true)
			{
				for(int m=n;m%i==0;m/=i)
				{
					count++;
					if(m%i==0)
					{
						if(count!=1)
							cout<<'*';
						cout<<i;
					}
				}
			}
	cout<<endl;
}
