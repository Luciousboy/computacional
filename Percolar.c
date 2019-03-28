

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int poblar(int *red,float p,int dim);
int imprimir(int *red, int dim);
int main()

{
	int dim = 3;
    	float p = 0.5;
	int *red;
	red=(int *)malloc(dim*dim*sizeof(int));  
	poblar(red, p,dim);
	imprimir(red,dim);
	//	clasificar(*red)
	free(red);
	return 0;
}

int poblar(int *red,float p,int dim)
{

    int i;  
    float rndm;
    srand(time(NULL));    
    for (i=0; i<dim*dim; i++)
    {
        rndm=(float)rand()/(float)RAND_MAX;

     	//  printf("%d", rndm);
      	//  printf("\n");
        *(red+i)=0;
        if (rndm < p)
        {
            *(red+i)=1;
        }

    } 
    return 0;
}

int imprimir(int *red, int dim)
    {
        int k, l;
        for (k=0; k<dim; k++)
	{
            for(l=0; l<dim; l++)
            {
		printf("%d", *(red+(dim*k+l)));
		}
	        printf("\n");
        }
    return 0;
    }

/*

int clasificar(int *red, int dim)
{
	if (red)
	{
	*red=2
	}
	for(i=1, i<dim,i++)
	{	
		if(red+i)
		{
			if(red+(i-1))		
			actualizar(red+i,historial,s,frag);
			
		}
	}
	for(i=1,i<dim,i++)
	{
		acutalizar(red+i*dim,historial,s,frag);
		for(j=1,j<dim,j++)
		{
			if(s1*s2)
			{
				etiqueta_falsa()
			}
			else
			{
				if(s1)
				{actializar(,s1)}
				else
				{actializar(,s2)}
			}
		}
	}
		
}

int actualizar(int *local,int *historial,int s,int frag)
{

	while(*historial+s<0)
		{
			s=-*historial+s;
		}
	*local=s
}

int etiqueta_falsa(*int local, int ĥistorial, int s1, int s2, int frac)
{

}

*/

