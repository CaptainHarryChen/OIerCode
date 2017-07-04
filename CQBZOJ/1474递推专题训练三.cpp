#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
int main()
{
    int n,f[20]={0};
    cin>>n;
	f[0]=1;
	f[1]=1;
	f[2]=2;
    for(int i=3;i<=n;i++)
    {
        int s=0;
        for(int j=1;j<=i;j++)
            s+=f[j-1]*f[i-j];
        f[i]=s;
    }
    cout<<f[n]<<endl;
    return 0;
}
