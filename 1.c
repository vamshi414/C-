#include<stdio.h>

int main()
{
	// count positions of set input nuumber
/*	int val,i,count=0;
	
	scanf("%d", &val);
	
	for(i=31;i>=0;i--)
	{
		if(val & 1<<i)
		{
			printf("%d\n", i);
			count++;
		}
	}
	
	printf("count:\n", count); */
	
	// verfies the ODD r EVEN
	/*int n;
	printf("enter the number:\n");
	scanf("%d", &n);
	
	n&=1;
	if(n)
	{
		printf("enter number is odd: %d\n", n);
	}
	else
	{
		printf("enter number is not odd: %d\n",n);
	}   */
	
	
	//euqal numbers
	
/*	int a,b;
	printf("enter the numbers:\n");
	scanf("%d%d", &a,&b);
	
	if(!(a^b))
	
	  printf("numebrs are equal:\n");
	else
	  printf("numbers r not equal:\n");  */
	  
	  
	  #define SWAP(x)   ((x & 0x00FF) <<8 ) | ((x & 0xFF00 ) >> 8)
	  
	  int i;
	  unsigned short int val;
	  printf("enter the ADDRESS");
	  scanf("%x", &val);
	  val = SWAP(val);
	  
	  printf("VAL:%x", val);
	  
	  
}
