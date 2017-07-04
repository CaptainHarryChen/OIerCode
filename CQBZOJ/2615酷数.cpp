#include<iostream> 
#include<cstdio> 
#include<cmath> 
using namespace std; 
bool x(int n) 
{ 
    if(n==1) 
        return 1; 
	int a=sqrt(n);
	if(a*a==n)
		return 1;
    return 0; 
} 
int main() 
{ 
    int a,b,cnt=0; 
    cin>>a>>b; 
    for(int i=pow(a,1.0/3),m=i*i*i;m<=b;i++,m=i*i*i) 
        if(m>=a&&x(m)) 
            cnt++; 
    cout<<cnt<<endl; 
    return 0; 
}