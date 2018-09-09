import java.util.Scanner;
import java.math.BigInteger;

public class Main {

	final static int MAXN=1005;
	static BigInteger fac[]=new BigInteger[MAXN];
	
	public static void main(String[] args) {
		int n,sum,cnt;
		int deg[]=new int[MAXN];
		
		Scanner cin=new Scanner(System.in);
		
		n=cin.nextInt();
		for(int i=1;i<=n;i++)
			deg[i]=cin.nextInt();
	
		fac[0]=BigInteger.ONE;
		for(int i=1;i<=n;i++)
			fac[i]=fac[i-1].multiply(new BigInteger(""+i));
		
		boolean flag=true;
		sum=n-2;
		cnt=0;
		BigInteger ans=BigInteger.ONE;
		for(int i=1;i<=n;i++)
			if(deg[i]!=-1)
			{
				if(sum<deg[i]-1)
				{
					flag=false;
					break;
				}
				ans=ans.multiply(fac[sum].divide(fac[sum-deg[i]+1]).divide(fac[deg[i]-1]));
				sum-=deg[i]-1;
				cnt++;
			}
		if(!flag)
			System.out.println(0);
		else
		{
			ans=ans.multiply(new BigInteger(""+(n-cnt)).pow(sum));	
			System.out.println(ans);
		}
		
		cin.close();
	}

}
