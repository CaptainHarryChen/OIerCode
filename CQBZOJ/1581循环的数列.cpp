#include<iostream> 
#include<cstdio> 
using namespace std; 
int main() 
{ 
    int n; 
    cin>>n; 
    int m[n]; 
    for(int i=0;i<n;i++) 
        cin>>m[i]; 
    for(int i=0;i<n;i++) 
    { 
        cout<<m[i]; 
        if(i!=n-1) 
            cout<<' '; 
    } 
    cout<<endl; 
}
