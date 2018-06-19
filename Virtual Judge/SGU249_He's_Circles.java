import java.util.*;
import java.math.BigInteger;

public class Solution
{
	static final int MAXN=200005;
	static int pri[],phi[],pcnt;
	static boolean npr[];
	public static void sieve()
	{
		pri=new int[MAXN];
		npr=new boolean[MAXN];
		phi=new int[MAXN];
		pcnt=0;
		npr[1]=true;
		phi[1]=1;
		for(int i=2;i<MAXN;i++)
		{
			if(!npr[i])
			{
				phi[i]=i-1;
				pri[++pcnt]=i;
			}
			for(int j=1;j<=pcnt&&(long)pri[j]*i<MAXN;j++)
			{
				npr[i*pri[j]]=true;
				if(i%pri[j]==0)
				{
					phi[i*pri[j]]=phi[i]*pri[j];
					break;
				}
				phi[i*pri[j]]=phi[i]*(pri[j]-1);
			}
		}
	}
	public static BigInteger pow(BigInteger a,int b)
	{
		BigInteger ret=new BigInteger("1");
		while(b!=0)
		{
			if((b&1)!=0)
				ret=ret.multiply(a);
			a=a.multiply(a);
			b>>=1;
		}
		return ret;
	}
	public static void main(String args[])
	{
		sieve();
		Scanner cin=new Scanner(System.in);
		int n=cin.nextInt();
		BigInteger ans=new BigInteger("0"),two=new BigInteger("2"),temp=new BigInteger("1");
		for(int i=1;(long)i*i<=n;i++)
		{
			if(n%i==0)
			{
				temp=(two.pow(i)).multiply(new BigInteger(Integer.toString(phi[n/i])));
				//System.out.println("temp:"+temp);
				ans=ans.add(temp);
				if(i!=n/i)
				{
					temp=(two.pow(n/i)).multiply(new BigInteger(Integer.toString(phi[i])));
					//System.out.println("temp:"+temp);
					ans=ans.add(temp);
				}
			}
			//System.out.println("ans"+i+":"+ans);
		}
		ans=ans.divide(new BigInteger(Integer.toString(n)));
		System.out.print(ans);
		cin.close();
	}
}
