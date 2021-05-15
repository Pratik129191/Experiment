import java.lang.*;
import java.util.*;

class Functions
{
	int digitCount(int number)
	{
		int count=0;
		while (number!=0)
		{
			count++;
			number=number/10;
		}
		return count;
	}

	int factorial(int number)
	{
		int fact=1;
		for(int i=1;i<=number;i++)
		{
			fact=fact*i;
		}
		return fact;
	}

	int rotate(int number)
	{
		int digit;
		digit=digitCount(number)-1;
		int result;
		result=(number%10) * (int) Math.pow(10,digit);
		number=number/10;
		result=result+number;
		return result;
	}

	int howManyPowerOfTwo(int num)
	{
		int count=0;
		int result=1;
		while (result<num)
		{
			result=result*2;
			count++;
		}
		if (result==num)
		{
			return count;
		}
		return 0;
	}

	int[] putInArray(int num)
	{
		int digit;
		digit=digitCount(num);
		int i;
		i=digit-1;
		int[] arr=new int[digit];
		while (num!=0)
		{
			arr[i]=num%10;
			num=num/10;
			i--;
		}
		return arr;
	}

	int sumOfArrayElements(int[] x)
	{
		int sum=0;
		for (int i : x)
		{
			sum = sum + i;
		}
		return sum;
	}

	int[] shiftLeftByOneAndPutItemAtLastInArray(int item,int[] arr)
	{
		for(int i=0;i<arr.length-1;i++)
		{
			arr[i]=arr[i+1];
		}
		arr[arr.length-1]=item;
		return arr;
	}
}

class Check
{
	Functions fun=new Functions();
	boolean isArmstrong(int number)
	{
		boolean flag=false;
		int sum=0,remind,copy=number;
		while (number!=0)
		{
			remind=number%10;
			sum=sum+(int)Math.pow(remind, fun.digitCount(copy));
			number=number/10;
		}
		if (copy==sum)
		{
			flag=true;
		}
		return flag;
	}

	boolean isAutomorphic(int number)
	{
		boolean flag=false;
		int sqr;
		sqr=number*number;
		int remind;
		remind=sqr % (int) Math.pow(10,fun.digitCount(number));
		if (remind==number)
		{
			flag=true;
		}
		return flag;
	}

	boolean isNeon(int number)
	{
		boolean flag=false;
		int sqr;
		sqr=number*number;
		int sum=0;
		int remind;
		while (sqr!=0)
		{
			remind=sqr%10;
			sum=sum+remind;
			sqr=sqr/10;
		}
		if (sum==number)
		{
			flag=true;
		}
		return flag;
	}

	boolean isMagic(int number)
	{
		boolean flag=false;
		while (fun.digitCount(number)!=1)
		{
			int sum=0,remind;
			while (number!=0)
			{
				remind=number%10;
				sum=sum+remind;
				number=number/10;
			}
			number=sum;
		}
		if (number==1)
		{
			flag=true;
		}
		return flag;
	}

	boolean isPalindrome(int number)
	{
		boolean flag=false;
		String str;
		str=Integer.toString(number);
		StringBuilder str_b=new StringBuilder(str);
		str_b.reverse();
		String str2;
		str2=str_b.toString();
		if (str.equals(str2))
		{
			flag=true;
		}
		return flag;
	}

	boolean isStrong(int number)
	{
		boolean flag=false;
		int sum=0,remind;
		while (number!=0)
		{
			remind=number%10;
			sum=sum+fun.factorial(remind);
			number=number/10;
		}
		if (sum==number)
		{
			flag=true;
		}
		return flag;
	}

	boolean isPrime(int number)
	{
		boolean flag=false;
		int count=0;
		for(int i=1;i<=number;i++)
		{
			if (number%i==0)
			{
				count++;
			}
		}
		if (count==2)
		{
			flag=true;
		}
		return flag;
	}

	boolean isAbundant(int number)
	{
		boolean flag=false;
		int sum=0,remind,copy=number;
		while (number!=0)
		{
			remind=number%10;
			sum=sum+remind;
			number=number/10;
		}
		if (sum>copy)
		{
			flag=true;
		}
		return flag;
	}

	boolean isDeficient(int number)
	{
		boolean flag=false;
		int sum=0,remind,copy=number;
		while (number!=0)
		{
			remind=number%10;
			sum=sum+remind;
			number=number/10;
		}
		if (sum<2*copy)
		{
			flag=true;
		}
		return flag;
	}

	boolean isKaprekar(int number)
	{
		boolean flag=false;
		int sqr,digit,first,second;
		sqr=number*number;
		digit=fun.digitCount(sqr);
		digit=digit/2;
		first=sqr % (int) Math.pow(10,digit);
		second=sqr / (int) Math.pow(10,digit);
		if (first+second==number && first!=0 && second!=0)
		{
			flag=true;
		}
		return flag;
	}

	boolean isLychrel(int number)
	{
		boolean flag=true;
		int MAX=30;
		for (int i=0;i<MAX;i++)
		{
			String str1;
			str1=Integer.toString(number);
			StringBuilder strb=new StringBuilder(str1);
			strb.reverse();
			String str2;
			str2=strb.toString();
			int result;
			result=Integer.parseInt(str1) + Integer.parseInt(str2);
			if (isPalindrome(result))
			{
				flag=false;
				break;
			}
		}
		return flag;
	}

	boolean isNarcissistic(int number)
	{
		boolean flag=false;
		if (isArmstrong(number))
		{
			flag=true;
		}
		return flag;
	}

	boolean isHappy(int number)
	{
		boolean flag=false;
		int MAX=30;
		for(int i=0;i<MAX;i++)
		{
			int sum=0,remind;
			while (number!=0)
			{
				remind=number%10;
				sum=sum + (int) Math.pow(remind,2);
				number=number/10;
			}

			if (sum==1)
			{
				flag=true;
				break;
			}
			else
			{
				number=sum;
			}
		}
		return flag;
	}

	boolean isDisarium(int number)
	{
		boolean flag=false;
		int sum=0,remind,count,copy=number;
		count= fun.digitCount(number);
		while (number!=0)
		{
			remind=number%10;
			sum=sum + (int) Math.pow(remind,count);
			count--;
			number=number/10;
		}
		if (sum==copy)
		{
			flag=true;
		}
		return flag;
	}

	boolean isHarshad(int number)
	{
		boolean flag=false;
		int sum=0,remind,copy=number;
		while (number!=0)
		{
			remind=number%10;
			sum=sum+remind;
			number=number/10;
		}
		if (copy%sum==0)
		{
			flag=true;
		}
		return flag;
	}

	boolean isPronicOrHeteromecic(int number)
	{
		boolean flag=false;
		for(int i=0;i<=(int) Math.sqrt(number);i++)
		{
			if (i*(i+1)==number)
			{
				flag=true;
				break;
			}
		}
		return flag;
	}

	boolean isDuck(int number)
	{
		boolean flag=false;
		String str;
		str=Integer.toString(number);
		Character check= str.charAt(0);
		Character zero='0';

		if (check.equals(zero))
		{
			return flag;
		}
		else
		{
			for(int i=1;i<str.length();i++)
			{
				check=str.charAt(i);
				if (check.equals(zero))
				{
					flag=true;
					break;
				}
			}
		}
		return flag;
	}

	boolean isAmicable(int num1,int num2)
	{
		boolean flag=false;
		int sum1=0,sum2=0;
		for(int i=1;i<=num1/2;i++)
		{
			if (num1%i==0)
			{
				sum1=sum1+i;
			}
		}
		for (int i=1;i<=num2/2;i++)
		{
			if (num2%i==0)
			{
				sum2=sum2+i;
			}
		}
		if (sum1==num2 && sum2==num1)
		{
			flag=true;
		}
		return flag;
	}

	boolean isCircularPrime(int number)
	{
		boolean flag=false;
		int digit;
		digit=fun.digitCount(number);
		for(int i=0;i<digit;i++)
		{
			if (isPrime(number))
			{
				flag=true;
				number=fun.rotate(number);
			}
			else
			{
				flag=false;
				break;
			}
		}
		return flag;
	}

	boolean isMersennePrime(int number)
	{
		boolean flag=false;
		int power;
		if(isPrime(number))
		{
			power= fun.howManyPowerOfTwo(number+1);
			if (power>=2)
			{
				flag=true;
			}
		}
		return flag;
	}

	boolean isKeith(int number)
	{
		boolean flag=false;
		int MAX=30;
		int[] arr= fun.putInArray(number);
		int result;
		for(int i=0;i<MAX;i++)
		{
			for(int j:arr)
			{
				System.out.print(j+" + ");
			}
			result= fun.sumOfArrayElements(arr);
			System.out.println("\b\b\b = "+result);
			if (result==number)
			{
				flag=true;
				break;
			}
			else
			{
				arr= fun.shiftLeftByOneAndPutItemAtLastInArray(result, arr);
			}
		}
		return flag;
	}
}

class Number_Checking
{
	public static void main(String[] args)
	{
		Scanner scan=new Scanner(System.in);
		Check chk=new Check();
		int number=0;
		int choice,option=1;
		
		while (option==1)
		{
			System.out.println("Check Various Types of Numbers........");
			System.out.println("\n1. ARMSTRONG_NUMBER.\n2. AUTOMORPHIC_NUMBER.\n3. NEON_NUMBER.\n4. MAGIC_NUMBER.\n5. PALINDROME_NUMBER.\n6. STRONG_NUMBER.\n7. PRIME_NUMBER.\n8. ABUNDANT_NUMBER.\n9. DEFICIENT_NUMBER.\n10. KAPREKAR_NUMBER.\n11. LYCHREL_NUMBER.\n12. NARCISSISTIC_NUMBER.\n13. HAPPY_NUMBER.\n14. DISARIUM_NUMBER.\n15. HARSHAD_NUMBER.\n16. PRONIC_NUMBER_or_HETEROMECIC_NUMBER.\n17. DUCK_NUMBER.\n18. AMICABLE_PAIR\n19. CIRCULAR_PRIME_NUMBER.\n20. MERSENNE_PRIME_NUMBER.\n21. KEITH_NUMBER.\n");
			System.out.print("Enter Your Choice:- ");
			choice=scan.nextInt();
			int num1=0,num2=0;
			if(choice==18)
			{
				System.out.print("Enter First Number:- ");
				num1=scan.nextInt();
				System.out.print("Enter Second Number:- ");
				num2=scan.nextInt();
			}
			else
			{
				System.out.print("\nEnter The Number:- ");
				number=scan.nextInt();
			}

			boolean flag;
			switch (choice)
			{
				case 1:
					flag=chk.isArmstrong(number);
					if (flag)
					{
						System.out.println("ARMSTRONG_NUMBER");
					}
					else
					{
						System.out.println("NON_ARMSTRONG_NUMBER");
					}
					break;
				case 2:
					flag=chk.isAutomorphic(number);
					if (flag)
					{
						System.out.println("AUTOMORPHIC_NUMBER.");
					}
					else
					{
						System.out.println("NON_AUTOMORPHIC_NUMBER.");
					}
					break;
				case 3:
					flag=chk.isNeon(number);
					if (flag)
					{
						System.out.println("NEON_NUMBER.");
					}
					else
					{
						System.out.println("NON_NEON_NUMBER.");
					}
					break;
				case 4:
					flag=chk.isMagic(number);
					if (flag)
					{
						System.out.println("MAGIC_NUMBER.");
					}
					else
					{
						System.out.println("NON_MAGIC_NUMBER.");
					}
					break;
				case 5:
					flag=chk.isPalindrome(number);
					if (flag)
					{
						System.out.println("PALINDROME_NUMBER.");
					}
					else
					{
						System.out.println("NON_PALINDROME_NUMBER.");
					}
					break;
				case 6:
					flag=chk.isStrong(number);
					if (flag)
					{
						System.out.println("STRONG_NUMBER.");
					}
					else
					{
						System.out.println("NON_STRONG_NUMBER.");
					}
					break;
				case 7:
					flag=chk.isPrime(number);
					if (flag)
					{
						System.out.println("PRIME_NUMBER.");
					}
					else
					{
						System.out.println("NON_PRIME_NUMBER.");
					}
					break;
				case 8:
					flag=chk.isAbundant(number);
					if (flag)
					{
						System.out.println("ABUNDANT_NUMBER.");
					}
					else
					{
						System.out.println("NON_ABUNDANT_NUMBER.");
					}
					break;
				case 9:
					flag=chk.isDeficient(number);
					if (flag)
					{
						System.out.println("DEFICIENT_NUMBER.");
					}
					else
					{
						System.out.println("NON_DEFICIENT_NUMBER.");
					}
					break;
				case 10:
					flag=chk.isKaprekar(number);
					if (flag)
					{
						System.out.println("KAPREKAR_NUMBER.");
					}
					else
					{
						System.out.println("NON_KAPREKAR_NUMBER.");
					}
					break;
				case 11:
					flag=chk.isLychrel(number);
					if (flag)
					{
						System.out.println("LYCHREL_NUMBER.");
					}
					else
					{
						System.out.println("NON_LYCHREL_NUMBER.");
					}
					break;
				case 12:
					flag=chk.isNarcissistic(number);
					if (flag)
					{
						System.out.println("NARCISSISTIC_NUMBER.");
					}
					else
					{
						System.out.println("NON_NARCISSISTIC_NUMBER.");
					}
					break;
				case 13:
					flag=chk.isHappy(number);
					if(flag)
					{
						System.out.println("HAPPY_NUMBER.");
					}
					else
					{
						System.out.println("NON_HAPPY_NUMBER.");
					}
					break;
				case 14:
					flag=chk.isDisarium(number);
					if (flag)
					{
						System.out.println("DISARIUM_NUMBER.");
					}
					else
					{
						System.out.println("NON_DISARIUM_NUMBER.");
					}
					break;
				case 15:
					flag=chk.isHarshad(number);
					if (flag)
					{
						System.out.println("HARSHAD_NUMBER.");
					}
					else
					{
						System.out.println("NON_HARSHAD_NUMBER.");
					}
					break;
				case 16:
					flag=chk.isPronicOrHeteromecic(number);
					if (flag)
					{
						System.out.println("PRONIC_or_HETEROMECIC_NUMBER.");
					}
					else
					{
						System.out.println("NON_PRONIC_or_NON_HETEROMECIC_NUMBER.");
					}
					break;
				case 17:
					flag=chk.isDuck(number);
					if (flag)
					{
						System.out.println("DUCK_NUMBER.");
					}
					else
					{
						System.out.println("NON_DUCK_NUMBER.");
					}
					break;
				case 18:
					flag=chk.isAmicable(num1,num2);
					if(flag)
					{
						System.out.println("AMICABLE_PAIRS.");
					}
					else
					{
						System.out.println("NON_AMICABLE_PAIRS.");
					}
					break;
				case 19:
					flag=chk.isCircularPrime(number);
					if (flag)
					{
						System.out.println("CIRCULAR_PRIME_NUMBER.");
					}
					else
					{
						System.out.println("NON_CIRCULAR_PRIME_NUMBER.");
					}
					break;
				case 20:
					flag=chk.isMersennePrime(number);
					if (flag)
					{
						System.out.println("MERSENNE_PRIME_NUMBER.");
					}
					else
					{
						System.out.println("NON_MERSENNE_PRIME_NUMBER.");
					}
					break;
				case 21:
					flag=chk.isKeith(number);
					if (flag)
					{
						System.out.println("\nKEITH_NUMBER.");
					}
					else
					{
						System.out.println("\nNON_KEITH_NUMBER.");
					}
					break;
				default:
					System.out.println("Wrong Choice.\n");
			}
			System.out.print("\n1.YES\n0. NO\nDo You Want to Continue:- ");
			option=scan.nextInt();
		}
	}
}