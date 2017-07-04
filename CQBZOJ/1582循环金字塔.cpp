#include<iostream> 
#include<cstdio> 
using namespace std; 
int main() 
{ 
    int n,i,j,k ; 
    scanf ("%d",&n) ; 
    for (i=1;i<=n;i++) 
    { 
        j=2*i-1 ; 
        for (k=1;k<=(2*n-1-j)/2;k++) 
            printf (" ") ; 
        for (j=1;j<=2*i-1;j++) 
            printf ("*") ; 
        printf ("\n") ; 
    } 
}
