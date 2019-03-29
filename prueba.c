
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//---------------------AVISO LAS FUNCIONES QUE VAMOS A USAR
int poblar(int *red,float p,int dim);
int imprimir(int *red, int dim);
int clasificar(int *red, int dim);
int actualizar(int *local,int *historial,int s,int frag);
int etiqueta_falsa(*int local, int historial, int s1, int s2, int frac);

//---------------------Main--------------------------------
int main()
{
	int dim = 3;
  float p = 0.5;
	int *red;
	red=(int *)malloc(dim*dim*sizeof(int));
	poblar(red, p, dim);
	imprimir(red,dim);
	clasificar(red,dim)
	free(red);
	return 0;
}

//---------------------FUNCIONES--------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int poblar(int *red,float p,int dim)
{
  int i;
  float rndm;
  srand(time(NULL));
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
//*************************************************************
int clasificar(int *red, int dim)
{
	int i;
	int frag=2;
	//para la primera fila no tiene que hacer nada
	if(*(red)) //si el contendio es 0 lo deja sino lo cambia por un 2
	{
		*red=frag;
	}
	for(i=1; i<dim;i++) //para la segunda fila
	{
		if(*(red+i)==*(red+(i-1)))
		{
			actualizar(red+i,historial,s,frag); //actualizo el valor en el que me paro y el del frag
		}
	}
	for(i=1;i<dim;i++)
	{
	acutalizar(red+i*dim,historial,s,frag);
	for(j=1;j<dim;j++)
	{
		if(s1*s2)
		{
		etiqueta_falsa();
		}
		else
		{
		if(s1)
		{
			actualizar(,s1)}
		}
		else
		{
			actualizar(,s2)}
		}
		}
		}
return 0;
		}
//*************************************************************
int crear_etiquetas(int *red,int frag)
{
	int i;
	int frag=2;
	//Para el caso a) no se hace nada
	//Ahora hago el caso b)
	for(i=1; i<dim;i++) //para la primera fila
	{
		if(*(red)) //si el contendio es 0 lo deja sino lo cambia por un 2
		{
			*red=frag;
		}
	//Ahora hago el caso c)
		if(*(red))
		{
			*red=frag;
		}
	//Ahora hago el caso d)

	while(*historial+s<0)
		{
			s=-*historial+s;
		}
	*local=s
}
//*************************************************************
int etiqueta_falsa(*int local, int historial, int s1, int s2, int frac)
{

}
//*************************************************************
int actualizar(int *local,int *historial,int s,int frag)
{
	while(*historial+s<0)
		{
			s=-*historial+s;
		}
	*local=s
}
