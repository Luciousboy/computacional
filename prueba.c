
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()

{
	int i
	int dim = 3;
    	float p = 0.5;
	int *red[dim*dim];  
	for(i=0, i<dim*dim,i++)
	{*red+i=1;
	}

 
        int k, l;
        for (k=0; k<dim; k++)
	{
            for(l=0; l<dim; l++)
            {
		printf("%i", *(red+(dim*k+l)));
		}
	        printf("\n");
        }
    
	return 0;
}
