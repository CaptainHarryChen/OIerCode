#include<cstdio>
#include<bitset>
using namespace std;
struct SuperLong:public bitset<150>
{
	SuperLong(){}
	SuperLong(const bitset<150> &t)
	{
		for(int i=140;i>=0;i--)
			this->set(i,t[i]);
	}
	int length()const
	{
		int len=140;
		while(len>=0&&!this->test(len))
			len--;
		return len+1;
	}
	void operator = (const SuperLong &t)
	{
		for(int i=140;i>=0;i--)
			this->set(i,t[i]);
	}
	bool operator < (const SuperLong &t)const
	{
		for(int i=140;i>=0;i--)
			if(this->test(i)<t[i])
				return 1;
			else if(this->test(i)>t[i])
				return 0;
		return 0;
	}
	bool operator > (const SuperLong &t)const
	{
		for(int i=140;i>=0;i--)
			if(this->test(i)>t[i])
				return 1;
			else if(this->test(i)<t[i])
				return 0;
		return 0;
	}
	bool operator <= (const SuperLong &t)const
	{
		for(int i=140;i>=0;i--)
			if(this->test(i)<t[i])
				return 1;
			else if(this->test(i)>t[i])
				return 0;
		return 1;
	}
	SuperLong operator + (const int &t)const
	{
		return *this+SuperLong(t);
	}
	SuperLong operator - (const int &t)const
	{
		return *this-SuperLong(t);
	}
	SuperLong operator + (const SuperLong &t)const
	{
		SuperLong ret=*this;
		bool flag=0;
		for(int i=0;i<=140;i++)
			if(flag)
			{
				if(!ret[i]&&!t[i])
					flag=0;
				ret[i]=!(ret[i]^t[i]);
			}
			else
			{
				if(ret[i]&&t[i])
					flag=1;
				ret[i]=ret[i]^t[i];
			}
		return ret;
	}
	SuperLong operator - (const SuperLong &t)const
	{
		SuperLong ret=*this;
		bool flag=0;
		for(int i=0;i<=140;i++)
			if(flag)
			{
				if(ret[i]>t[i])
					flag=0;
				ret[i]=!(ret[i]^t[i]);
			}
			else
			{
				if(ret[i]<t[i])
					flag=1;
				ret[i]=ret[i]^t[i];
			}
		return ret;
	}
	SuperLong operator * (int t)const
	{
		SuperLong tmp=*this,ret=SuperLong(0);
		while(t)
		{
			if(t&1)
				ret=ret+tmp;
			tmp<<=1;
			t>>=1;
		}
		return ret;
	}
	void print()
	{
		char pow2[80]={1},pro[80]={0};
		int flag;
		int len=this->length();
		if(len==0)
		{
			printf("0\n");
			return;
		}
		for(int i=0;i<len;i++)
		{
			if(this->test(i))
			{
				flag=0;
				for(int j=0;j<80;j++)
				{
					pro[j]+=pow2[j]+flag;
					flag=pro[j]/10;
					pro[j]%=10;
				}
			}
			flag=0;
			for(int j=0;j<80;j++)
			{
				pow2[j]+=pow2[j]+flag;
				flag=pow2[j]/10;
				pow2[j]%=10;
			}
		}
		int k;
		for(k=79;k>=0&&pro[k]==0;k--);
		for(;k>=0;k--)
			printf("%d",pro[k]);
		puts("");
	}
};
SuperLong dp[105],pow2[105];
void Init()
{
	pow2[0]=SuperLong(1);
	for(int i=1;i<=100;i++)
	{
		dp[i]=(SuperLong)(dp[i-1]<<1)+pow2[i-1];
		pow2[i]=pow2[i-1]<<1;
	}
}
SuperLong GetRank(SuperLong x)
{
	SuperLong ret,cnt;
	int len=x.length();
	for(int i=0;i<len;i++)
		if(x.test(i))
		{
			ret=ret+dp[i]+cnt;
			cnt=cnt+pow2[i];
		}
	return ret;
}
SuperLong Search(int K,SuperLong rank)
{
	SuperLong ret,tmp;
	if(!(rank<dp[K]))
	{
		ret[K]=1;
		return ret;
	}
	int cnt=0;
	for(int i=K-1;i>=0;i--)
	{
		tmp=dp[i]+pow2[i]*cnt;
		if(tmp<=rank)
		{
			rank=rank-tmp;
			cnt++;
			ret[i]=1;
		}
	}
	return ret;
}
int main()
{
	Init();
	int K,M,i;
	scanf("%d%d",&K,&M);
	SuperLong L,R,mid,a,b,ed;
	ed[K]=1;
	R=dp[K];
	while(L<R)
	{
		mid=(L+R)>>1;
		a=SuperLong(0);
		i=0;
		do
		{
			a=Search(K,mid+GetRank(a));
			i++;
		}while(a<ed&&i<M);
		if(!(a<ed))
			R=mid;
		else
			L=mid+1;
	}
	L.print();
	return 0;
}
