#include<iostream>
#include<string>
using namespace std;

class ThueMorseGame
{
	int pc[(1<<16)];
public:
	string get(int n,int m)
	{
		if(n<=m)
			return "Alice";
		for(int k=0;k<(1<<16);k++)
			pc[k]=__builtin_popcount(k)&1;
		int i=0;
		do
		{
			i=i+m+1;
			while(pc[i&((1<<16)-1)]^pc[i>>16])
				i++;
		}while(i<n);
		if(i==n)
			return "Bob";
		return "Alice";
	}
};

