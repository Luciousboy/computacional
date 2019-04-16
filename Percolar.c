
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//---------------------AVISO LAS FUNCIONES QUE VAMOS A USAR
int poblar(int *red,float p,int dim);
int imprimirMat(int *red, int dim);
int imprimirVector(int *vect, int dim);
int clasificar(int *red, int dim, int *historial,int etiqueta);
int actualizar(int *local,int *historial,int s,int etiqueta);
int etiqueta_falsa(int *local, int *historial, int s1, int s2, int etiqueta);
int arreglar_etiquetas(	int *red,int *historial, int dim);
int percola(int *red, int dim);
int percola_fragmentos(int *red, int dim);

//---------------------Main--------------------------------
int main()

{
	FILE * fp;
	srand(time(NULL));
	int *red_dim;
	red_dim=(int *)malloc( 5*sizeof(int));//multiplico por 5 porque son 5 elementos
	*(red_dim)=4;
	*(red_dim+1)=16;
	/*for(j=2;j<5;j++) //para llenarlo con las otras dimensiones
	{	*(red_dim+j)=*(red_dim+j-1)*2;
	}*/
	int i;
	for (i=0;i<2;i++) //cambiar por i<5 si hacemos todos los casos
	{	int dim=*(red_dim+i);
		int etiqueta=2;
		int *red;
		int b;
		int k;
		int l;
		int h=0;
		int p_mean=0;
		red=(int *)malloc(dim * dim *sizeof(int));
		int *historial;
		historial=(int *)malloc( dim*dim*sizeof(int));
		int r;
		while (h<27000)
		{	float p = 0.5;
			float dp = 0.5;
			l=rand();
			for (k=0;k<10;k++)
			{ for(r=0;r<dim*dim;r++)//Armar el historial
				{*(historial+r)=r;
				}
				srand(l); //si pongo h podria detectar errores
				poblar(red, p,dim);
				clasificar(red, dim,historial,etiqueta);
				arreglar_etiquetas(red, historial, dim);
				b=percola(red, dim);
//				b,k=percola_fragmentos(red, dim);
				dp = dp/2;

				if (b){
	//			printf("¡Percoló!");
				p = p-dp;
				}else{
	//			printf("Nope, no percoló");
				p=p+dp;
				}
			h++;
			//defino el p_mean
			p_mean = (p_mean + p) /27000;

	//guardo todos los p
			if (h<27000) {
				fp = fopen ("valores_de_p.txt", "a");
				fprintf(fp,"%f ",p_mean);
				fclose(fp);
			} else {
				fp = fopen ("valores_de_p.txt", "a");
				fprintf(fp,"\n \n \n");
				fclose(fp);}
		}
		}
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
	while(*(historial+s)<0)
		{
			s=-*(historial+s);
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
	while(*(historial+s1)<0)
	{
		s1=-(*(historial+s1));
	}
	while(*(historial+s2)<0)
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

// armo los vectores
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
	}if(*(red+(dim*(dim-1))+i)>0) //Le especifique el >0 por si *(red+(dim*(dim-1))+i) llega a ser =! 0,1
	{
	*(vect2+*(red+(dim*(dim-1))+i))=1;
	}
}

/*estamos comparando miembro a miembro, nos perdemos si percola
cuando tenemos un elemento en la posicion i y otro en la i+1 */
/* idea para solucionarlo, es comparar si directamente *(red+i) == *(red+(dim*(dim-1))+i)
entonces si es verdadero pertenecen al mismo grupo, entonces percolaron
*/
while (*(vect1+j) * *(vect2+j)==0 && j<dim*dim)
{
j++;
}

if (j<dim*dim)
b=1;
return b;
}
//*************************************************************
int percola_fragmentos(int *red, int dim)
{
	int i;
	int j;
	int k=0;
	int b=0;
	/* Siguiendo la misma idea de comparar si directamente *(red+i) == *(red+(dim*(dim-1))+i)
	podemos contar cada vez que ocurre entonces van a ser la cantidad de fragrmentos que percolaron.
	*/
for (i=0; i<dim; i++)
{//tengo que buscar en tooodos contra tooodos los elementos para evitar el problema de arriba
	for (j=0; j<dim; j++)
	{	if(*(red+i) == *(red+(dim*(dim-1))+j) && *(red+i)>1 ) //tengo que excluir los casos con 1, porque son aislados (chequiar)
		{k++; //cada vez que percola y son del mismo grupo entonces sumo 1
		}
	}
}
if (k>0)
{b=1; //O sea, percoló y además lo hizo k veces.
}
return b,k;
}
