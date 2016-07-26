#include <stdio.h>

int main()
{
		int a=0;
	int  mas[10][10];

	for(int i=0; i<10; i++)
 	{
  		for(int j=0; j<10; j++)
  		{
				mas[i][j] = a;
				a=a+1;
			
   			printf("%d ", mas[i][j]);
  		}
  		printf("\n");
  	}

}
