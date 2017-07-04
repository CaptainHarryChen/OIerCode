#include <iostream>
using namespace std;
int main()
{
	int cnt=0;
    for(int i=1;cnt<10;i++)
		if(i%2==1&&i%3==1&&i%5==1)
		{
			cout<<i<<endl;
			cnt++;
		}
	return 0;
}
