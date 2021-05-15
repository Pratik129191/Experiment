import java.lang.*;
import java.util.*;

class Functions
{
	private int[] reverseArray(int[] array)
	{
		int arrayc[]=new int[array.length];
		int x=0;
		for(int i=(array.length - 1);i>=0;i--)
		{
			arrayc[x]=array[i];
			x++;
		}
		return arrayc;
	}
	private int[] decimalToBinaryConverter(int element,int size)
	{
		int array[]=new int[size];
		if(element==0)
		{
			for(int i=0;i<array.length;i++)
			{
				array[i]=0;
			}
		}
		if(element!=0)
		{
			int rest,i=0;
			while(element!=0)
			{
				rest=element%2;
				array[i]=rest;
				i++;
				element=element/2;
			}
		}
		array=reverseArray(array);
		return array;
	}
	private int[][] inputLogic(int input)
	{
		int count=(int)Math.pow(2,input);
		int array[][]=new int[count][];
		for(int i=0;i<array.length;i++)
		{
			array[i]=new int[input];
		}
		for(int i=0;i<count;i++)
		{
			array[i]=decimalToBinaryConverter(i,input);
		}
		return array;
	}
	private int[] outputLogic(int input)
	{
		int array[][]=new int[(int)Math.pow(2,input)][];
		for(int i=0;i<array.length;i++)
		{
			array[i]=new int[input];
		}
		array=inputLogic(input);
		int out[]=new int[array.length];
		for(int i=0;i<array.length;i++)
		{
			int mul=0;
			for(int j=0;j<array[i].length;j++)
			{
				mul=mul+array[i][j];
			}
			if(mul==1 || mul>1)
			{
				out[i]=0;
			}
			if(mul==0)
			{
				out[i]=1;
			}
		}
		return out;
	}
	protected void norGate(int input)
	{
		int inputs[][]=new int[(int)Math.pow(2,input)][];
		inputs=inputLogic(input);
		int outputs[]=new int[inputs.length];
		outputs=outputLogic(input);
		System.out.println("\n Inputs\t\t    Outputs\n\n");
		for(int i=0;i<inputs.length;i++)
		{
			for(int j=0;j<inputs[i].length;j++)
			{
				System.out.print(inputs[i][j]+"  ");
			}
			System.out.println("\t\t"+outputs[i]+"\n");
		}
	}
}

class NorGate
{
	public static void main(String[] pratik)
	{
		Scanner obj=new Scanner(System.in);
		Functions fun=new Functions();
		int input;
		System.out.print("Enter The Input Bits Number:- ");
		input=obj.nextInt();
		fun.norGate(input);
	}
}