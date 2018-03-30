#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
const int MAXN=55;

int id[MAXN];
char ans[100];
//[L,R]区间的字典序最小值
int FindMin(int L,int R)
{
	int res=L;
	long long temp=1;
	while(temp<res)
		temp*=10LL;
	if(temp<=R)
		return temp;
	return res;
}

class CakeParty
{
public:
	string makeMove(vector<int>&);
};
//最大值的个数为偶数时，先手必输
//此时先手无论如何走，后手必有方法抄袭先手
string CakeParty::makeMove(vector<int> &p)
{
	int n=p.size();
	//1个蛋糕直接吃完
	if(n==1)
	{
		sprintf(ans,"CAKE 0 PIECES %d",p[0]);
		return ans;
	}
	//预处理字典序蛋糕编号
	id[0]=0;
	for(int i=1,j=1;i<5;i++)
	{
		id[j++]=i;
		for(int k=0;k<10;k++)
			id[j++]=i*10+k;
		if(i==4)
			for(int k=5;k<10;k++)
				id[j++]=k;
	}
	
	int cnt1=0,cnt2=0;
	int mx=0,mx2=0;
	//记录最大值，和最大值的个数
	for(int i=0;i<n;i++)
		mx=max(mx,p[i]);
	for(int i=0;i<n;i++)
		cnt1+=p[i]==mx;
	//cnt1>1时
	//若最大值个数为奇数，是其中一个最大值-1，使得最大值个数为偶数最优
	//若最大值个数为偶数，直接认输，取最小字典序的最大值编号吃一个
	if(cnt1>1)
	{
		for(int i=0;i<50;i++)
			if(p[id[i]]==mx)
			{
				sprintf(ans,"CAKE %d PIECES %d",id[i],1);
				return ans;
			}
	}
	//此时最大值只有一个
	//记录第二大值和第二大值个数
	for(int i=0;i<n;i++)
		if(p[i]!=mx)
			mx2=max(mx2,p[i]);
	for(int i=0;i<n;i++)
		cnt2+=p[i]==mx2;
	//第二大值有偶数个，则把最大值吃得比第二大值小最优
	if(cnt2%2==0)
	{
		for(int i=0;i<50;i++)
			if(p[id[i]]==mx)
			{
				sprintf(ans,"CAKE %d PIECES %d",id[i],FindMin(mx-mx2+1,mx));
				return ans;
			}
	}
	//第二大值有奇数个，把最大值吃得与第二大值一样最优
	for(int i=0;i<50;i++)
		if(p[id[i]]==mx)
		{
			sprintf(ans,"CAKE %d PIECES %d",id[i],mx-mx2);
			return ans;
		}
	return "ERROR";
}

vector<int> a;
CakeParty CP;
int main()
{
	int n;
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		a.push_back(x);
	}
	cout<<CP.makeMove(a)<<endl;
	return 0;
}
