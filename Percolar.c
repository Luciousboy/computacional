
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int poblar(int *red,float p,int dim);
int imprimir(int *red, int dim);
int clasificar(int *red, int dim);
int actualizar(int *local,int *historial,int s,int frag);
int etiqueta_falsa(int *local, int *historial, int s1, int s2, int frac);

int main()

{
	int dim = 5;
    	float p = 0.5;
	int *red;
	red=(int *)malloc(dim*dim*sizeof(int));  
	poblar(red, p,dim);
	imprimir(red,dim);
	clasificar(red,dim);
	printf("\n");
	imprimir(red,dim);
	free(red);	
	printf("\n");
	
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


int clasificar(int *red, int dim)
{
	int *historial;
	historial=(int *)malloc(dim*sizeof(int));
	int j,i;	
	int etiqueta=2;
	int s1;
	int s2;
	for(j=0;j<dim*dim;j++)//Armar el historial
	{*(historial+j)=j;	
	}
	
	
	
	if (*red)// la primer celda
	{
	*red=etiqueta;
	etiqueta++;
	}
	for(i=1; i<dim;i++)//La primer fila
	{	
		if(*(red+i)>0)// Si tiene un 1
		{
			if(*(red+(i-1))>0) // Si la de atrás tiene un 1
			{		
			actualizar(red+i,historial,*(red+(i-1)),etiqueta);
			}else{ // Si tiene que poner una etiqueta nueva

			*(red+i)=etiqueta;
			etiqueta++;
			}
		}
	}
	
	for(j=1;j<dim;j++) //el resto de las filas
	{

		if(*(red+j*dim)>0) // La primer columna de cada fila, si tiene un 1
		{

			if(*(red+(j-1)*dim)>0) // Si la de arriba tiene un 1
			{ 
			actualizar(red+j*dim,historial,*(red+(j-1)*dim),etiqueta);
			}else{//Si tiene que agregar una nueva etiqueta

			*(red+j*dim)=etiqueta;
			etiqueta++;
			}
		}
		for(i=1;i<dim;i++) // el resto de las columnas
		{

				if(*(red+j*dim+i)>0) // si tiene un 1

				{
					
					s1=*(red+j*dim+i-1); // la de arriba
					s2=*(red+(j-1)*dim+i);	// la de la izquierda

					if(s1+s2==0)
					{
					*(red+j*dim+i)=etiqueta;
					etiqueta++;	
					}else{
						if(s1*s2>0) // si las dos son positivas
						{

						etiqueta_falsa((red+j*dim+i),historial,s1,s2,etiqueta);

						}
						else
						{
							if(s1>0)
							{actualizar((red+j*dim+i),historial,s1,etiqueta);
							}
							else
							{actualizar((red+j*dim+i),historial,s2,etiqueta);
							}
						}
					}
				}
		}
		
	}
	printf("\n Historial: ");
	for (i=0;i<dim*dim;i++)
	{
		printf("%d",*(historial+i));
	}	
	printf("\n");
	return 0;
}



int actualizar(int *local,int *historial,int s,int frag)
{
	while(*historial+s<0)
		{
			s=-*historial+s;
		}
	*local=s;
	return 0;
}

int etiqueta_falsa(int *local, int *historial, int s1, int s2, int frac)
{
	int mini,maxi;
	while(*historial+s1<0)
	{
		s1=-(*(historial+s1));
	}
	while(*historial+s2<0)
	{
		s2=-(*(historial+s2));
	}
	if(s1<s2)
	{
	mini=s1;
	maxi=s2;
	}else{
	mini=s2;
	maxi=s1;
	}
	*local=mini;
	*(historial+maxi)=-mini;
	*(historial+mini)=mini;
	return 0;
}	
// Creo que anda bien. Habría que revisar un poco más que pasa con más casos. 
// Falta: Reetiquetar todo, ver si percola o no

