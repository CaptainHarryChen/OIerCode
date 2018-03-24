#include<cstdio>
#include<cmath>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int MAXN=26,MAXS=(1<<12)+10;
const double EPS=1e-10;

class NewItemShop
{
	int Input(char *&input)
	{
		int x=0;
		while(*input!='\0')
		{
			if('0'<=*input&&*input<='9')
			{
				x=*input-'0';
				input++;
				while('0'<=*input&&*input<='9')
				{
					x=x*10+*input-'0';
					input++;
				}
				return x;
			}
			input++;
		}
		return EOF;
	}
	int fcmp(double a,double b)
	{
		if(fabs(a-b)<EPS)
			return 0;
		if(a<b)
			return -1;
		return 1;
	}
	
	struct Customer
	{
		int id,val,p;
		Customer(){id=-1;}
		Customer(int _i,int _v,int _p)
		{id=_i;val=_v;p=_p;}
	};
	
	bool record[MAXN];
	int newId[MAXN];
	Customer cus[MAXN];
	double P[MAXN];
	bool vis[MAXN][MAXN][MAXS];
	double dp[MAXN][MAXN][MAXS];//卖i个sword，前j小时，有s状态的顾客来过的最大期望
	
	double DP(int swords,int hour,int s)
	{
		if(swords==0||hour==24)
			return 0.0;
		if(vis[swords][hour][s])
			return dp[swords][hour][s];
		vis[swords][hour][s]=true;
		if(cus[hour].id==-1)//没人来
			return dp[swords][hour][s]=DP(swords,hour+1,s);
		if(!record[cus[hour].id])//只来一次
		{
			dp[swords][hour][s]=(P[cus[hour].id]-cus[hour].p)/P[cus[hour].id]*DP(swords,hour+1,s);//该来的没来
			dp[swords][hour][s]+=1.0*cus[hour].p/P[cus[hour].id]*//来了
			max(DP(swords,hour+1,s),//不卖
				DP(swords-1,hour+1,s)+cus[hour].val);//卖一个
			return dp[swords][hour][s];
		}
		else
		{
			int add=1<<newId[cus[hour].id];
			if(s&add)//以前来过
				return dp[swords][hour][s]=DP(swords,hour+1,s);
			P[cus[hour].id]-=cus[hour].p;
			dp[swords][hour][s]=1.0*P[cus[hour].id]/(P[cus[hour].id]+cus[hour].p)*DP(swords,hour+1,s);//该来的没来
			P[cus[hour].id]+=cus[hour].p;
			dp[swords][hour][s]+=1.0*cus[hour].p/P[cus[hour].id]*//来了
			max(DP(swords,hour+1,s^add),//不卖
				DP(swords-1,hour+1,s^add)+cus[hour].val);//卖一个
			return dp[swords][hour][s];
		}
	}
	
public:
	double getMaximum(int swords,vector<string> &customers)
	{
		int n=customers.size();
		for(int i=0;i<n;i++)
		{
			int T,C,p,j=0;
			char *stream=(char*)customers[i].c_str();
			while(T=Input(stream),C=Input(stream),p=Input(stream),p!=EOF)
				cus[T]=Customer(i,C,p),j++;
			if(j>1)
				record[i]=true;
			P[i]=100;
		}
		int m=0;
		for(int i=0;i<n;i++)
			if(record[i])
				newId[i]=m++;
		return DP(swords,0,0);
	}
};
