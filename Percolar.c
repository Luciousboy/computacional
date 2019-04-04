
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//---------------------AVISO LAS FUNCIONES QUE VAMOS A USAR
int poblar(int *red,float p,int dim);
int imprimirMat(int *red, int dim);
int imprimirVector(int *vect, int dim);
int clasificar(int *red, int dim, int *historial,int etiqueta);
int actualizar(int *local,int *historial,int s,int etiqueta);
int etiqueta_falsa(int *local, int *historial, int s1, int s2, int etiqueta);
int arreglar_etiquetas(	int *red,int *historial, int dim);
int percola(int *red, int dim);

//---------------------Main--------------------------------
int main()

{
	srand(time(NULL));
	int dim = 5;
	float p = 0.5;
	float dp = 0.5;
	int etiqueta=2;
	int *red;
	int b;
	int k;
	int l;
	int h=0;
	red=(int *)malloc(dim*dim*sizeof(int));
	int *historial;
	historial=(int *)malloc(dim*dim*sizeof(int));
	int r;
	while (h<27000)
	{
		l=rand();
		for (k=0;k<10;k++)
		{
			for(r=0;r<dim*dim;r++)//Armar el historial
			{*(historial+r)=r;
			}
			srand(l); //si pongo h podria detectar errores
			poblar(red, p,dim);
			printf("Red Originial: \n");
			imprimirMat(red,dim);

			clasificar(red,
			dim,historial,etiqueta);
			printf("Historial: \n");
			imprimirVector(historial,dim);

			printf("Red modificada: \n");
			imprimirMat(red,dim);

			arreglar_etiquetas(red, historial, dim);
			printf("Red arreglada: \n");
			imprimirMat(red,dim);

			b=percola(red, dim);
			dp = dp/2;
			if (b)
			{printf("¡Percoló!");
			p = p-dp;
			}else{
			printf("Nope, no percoló");
			p=p+dp;
			}
			printf("\n");
			//fopen(); esto es para guardar en txt
			printf("%f",p);
			//fclose();
		}
		h++;
		free(red);
	}
	return 0;
}

//---------------------FUNCIONES--------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int poblar(int *red,float p,int dim)
{
  int i;
  float rndm;
  for (i=0; i<dim*dim; i++)
  {
    rndm=(float)rand()/(float)RAND_MAX;
    *(red+i)=0;
    if (rndm < p)
    {
        *(red+i)=1;
    }
  }
  return 0;
}
//*************************************************************
int imprimirMat(int *red, int dim)
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
	printf("\n");
    return 0;
    }
//*************************************************************
int imprimirVector(int *vect, int dim)
    {
        int k;
        for (k=0; k<dim*dim; k++)
	{printf("%d", *(vect+k));
        }
	 printf("\n");

    return 0;
    }
//*************************************************************
int clasificar(int *red, int dim,int *historial,int etiqueta)
{

	int j,i;
	int s1;
	int s2;

	if (*red)// la primer celda
	{
	*red=etiqueta;
	etiqueta++;
	}
	for(i=1; i<dim;i++)//La primer fila
	{
		if(*(red+i)>0)// Si tiene un 1
			etiqueta=actualizar(red+i,historial,*(red+(i-1)),etiqueta);

	}

	for(j=1;j<dim;j++) //el resto de las filas
	{

		if(*(red+j*dim)>0) // La primer columna de cada fila, si tiene un 1
			etiqueta=actualizar(red+j*dim,historial,*(red+(j-1)*dim),etiqueta);

		for(i=1;i<dim;i++) // el resto de las columnas
		{

				if(*(red+j*dim+i)>0) // si tiene un 1
				{

					s1=*(red+j*dim+i-1); // la de la izquierda
					s2=*(red+(j-1)*dim+i);	// la de arriba

						if(s1*s2>0) // si las dos son positivas
						{
						etiqueta_falsa((red+j*dim+i),historial,s1,s2,etiqueta);
						}
						else
						{
							if(s1>0)
							{etiqueta=actualizar((red+j*dim+i),historial,s1,etiqueta);
							}
							else
							{etiqueta=actualizar((red+j*dim+i),historial,s2,etiqueta);
							}
						}

				}
		}

	}

	return 0;
}

//*************************************************************

int actualizar(int *local,int *historial,int s,int etiqueta)
{

	if (s>0)
	{
	while(*historial+s<0)
		{
			s=-(*historial+s);
		}
	*local=s;
	}else{
	*local=etiqueta;
	etiqueta++;
	}
	return etiqueta;
}
//*************************************************************
int etiqueta_falsa(int *local, int *historial, int s1, int s2, int etiqueta)
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
//*************************************************************
int arreglar_etiquetas(	int *red,int *historial, int dim)
{
int i;
int s;
for (i=0; i<dim*dim; i++)
{	s=*(historial+*(red+i));
	while(s<0)
	{
	s= *(historial +(-s));
	}
	*(red+i)=s;
}
return 0;
}

//*************************************************************
int percola(int *red, int dim)
{
int i;
int j=0;
int k;
int b=0;
int *vect1;
vect1=(int *)malloc(dim*dim*sizeof(int));
int *vect2;
vect2=(int *)malloc(dim*dim*sizeof(int));

for(k=0;k<dim*dim;k++)
{
	*(vect1+k)=0;
	*(vect2+k)=0;
}

for (i=0; i<dim; i++)
{

	if (*(red+i)>0)
	{
	*(vect1+*(red+i))=1;
	}if(*(red+(dim*(dim-1))+i))
	{
	*(vect2+*(red+(dim*(dim-1))+i))=1;
	}
}

while (*(vect1+j) * *(vect2+j)==0 && j<dim*dim)
{
j++;
}

if (j<dim*dim)
b=1;

return b;
}
