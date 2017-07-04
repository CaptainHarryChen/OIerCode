#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int n;
    scanf ("%d",&n);
	if(n>20||n<=0){cout<<"no answer"<<endl;return 0;}
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=i-1;j++)
            printf (" ");
        for (int j=1;j<=2*(n-i+1)-1;j++)
            printf ("#");
        printf ("\n");
    }
	return 0;
}
