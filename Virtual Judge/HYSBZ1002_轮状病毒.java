import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner cin=new Scanner(System.in);
		int n;
		n=cin.nextInt();
		cin.close();
		if(n==1){System.out.println("1");return;}
		if(n==2){System.out.println("3");return;}
		if(n==3){System.out.println("16");return;}
		
		BigInteger N3=new BigInteger(String.valueOf(3));
		BigInteger a=new BigInteger(String.valueOf(3)),b=new BigInteger(String.valueOf(-1));
		for(int i=1;i<n-1;i++)
		{
			BigInteger t=a;
			a=t.multiply(N3).add(b);
			b=BigInteger.ZERO.subtract(t);
			if(i==n-2)
				b=b.subtract(BigInteger.ONE);
		}
		
		BigInteger c=BigInteger.ZERO.subtract(BigInteger.ONE),d=BigInteger.ZERO;
		for(int i=1;i<n-1;i++)
		{
			BigInteger t=c;
			c=t.multiply(N3).add(d);
			d=BigInteger.ZERO.subtract(t);
			if(i==n-3)
				d=d.subtract(BigInteger.ONE);
			if(i==n-2)
				d=d.add(N3);
		}

		
		while(!(c.equals(BigInteger.ZERO)))
		{
			BigInteger t=c.divide(a);
			c=c.subtract(a.multiply(t));
			d=d.subtract(b.multiply(t));
			if(c.equals(BigInteger.ZERO))
				break;
			t=a;a=c;c=t;
			t=b;b=d;d=t;
		}
		
		BigInteger ans=a.multiply(d);
		System.out.println(ans);
	}

}
