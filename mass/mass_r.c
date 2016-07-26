#include <stdio.h>

int main()
{
	int  mas[10][10];

	for(int i=0; i<10; i++)
 	{
  		for(int j=0; j<10; j++)
  		{
  			if ( i <= j)
				mas[i][j] = 1;
			else 
				mas[i][j] = 0;
   			printf("%d ", mas[i][j]);
  		}
  		printf("\n");
  	}

}
