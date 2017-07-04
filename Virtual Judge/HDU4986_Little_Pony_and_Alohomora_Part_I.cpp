#include<cstdio>
#include<cmath>
int n;const int a=1000000;double b[a+1];int main(){for(int i=1;i<=a;i++)b[i]=b[i-1]+1.0/i;while(~scanf("%d",&n))if(n<=a)printf("%.4lf\n",b[n]);else printf("%.4lf\n",0.577215664901+log(n*1.0)+1.0/(2*n));return 0;}