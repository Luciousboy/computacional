
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
int ns(int *red, int dim, int *size);

//---------------------Main--------------------------------
int main()

{
	srand(time(NULL));

	//Hacer el ejercicio con 5 grillas distintas
	int *red_dim;
	red_dim=(int *)malloc( 5*sizeof(int));//multiplico por 5 porque son 5 elementos
	*(red_dim)=4;
	*(red_dim+1)=16;
	int j;
	for(j=2;j<5;j++) //para llenarlo con las otras dimensiones
	{	*(red_dim+j)=*(red_dim+j-1)*2;
	}
	int i;
	for (i=3;i<5;i++) //cambiar por i<5 si hacemos todos los casos
		{float p=0.57;
		float dp=0.01;
		int iteraciones=0;
		int iteraciones_max=27000;
		int dim=*(red_dim+i);


		//Para guardar
		FILE *fp;
		char filename[64];
		sprintf(filename,"Ej2y3_L=%d.txt",dim);
		fp=fopen(filename,"w");
		//Aca empieza el ejercicio para una grilla
		int etiqueta=2;

		int b;
		int l;
		int *red;
		red=(int *)malloc(dim * dim *sizeof(int));
		int *historial;
		historial=(int *)malloc( dim*dim*sizeof(int));

		int r;
		while (p<1)
			{float b_mean=0;
			float percolacion=0;
			int percolo=0;
			int b_tot=0;
			while (percolo<iteraciones_max)
			{l=rand();
			srand(l);
				for(r=0;r<dim*dim;r++)//Armar el historial
				{*(historial+r)=r;}
			poblar(red, p,dim);
			clasificar(red, dim,historial,etiqueta);
			arreglar_etiquetas(red, historial, dim);
			b=percola(red, dim);//Masa
				if(b>0)
				{
				percolo++;
				b_tot=b_tot+b;
				
				}
			


			iteraciones++;
			}
			//1º probabilidad 2º masa 3º porcentaje de percolacion
			fprintf(fp,"%f ", p);
			b_mean=(float)b_tot/(float)percolo;			

			fprintf(fp,"%f ", b_mean);

			percolacion=(float)percolo/(float)iteraciones;
			fprintf(fp,"%f ",percolacion);
			fprintf(fp,"\n");

			p=p+dp;
			}


		fclose(fp);
		free(red);
		free(historial);
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
int b=0;
int *vect1;
vect1=(int *)malloc(dim*dim*sizeof(int));
int *vect2;
vect2=(int *)malloc(dim*dim*sizeof(int));
int r;
int k;
for(r=0;r<dim*dim;r++)//Armar el historial
	{*(vect1+r)=0;
	*(vect2+r)=0;
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
{

    for (i=0; i<dim; i++)
    {

        for (k=0; k<dim; k++)
        {
            if (*(red+i*dim+k)==j){

            b++;
            }
        }
    }
}
free(vect1);
free(vect2);
return b;
}


//*************************************************************
int ns(int *red, int dim, int *size)
{
    int i;
    int j;
    int k;
    int *etiquetas;
    etiquetas=(int *)malloc( dim*dim*sizeof(int));
    /* Siguiendo la misma idea de comparar si directamente *(red+i) == *(red+(dim*(dim-1))+i)
    podemos contar cada vez que ocurre    */
    // armo los vectores
    for(k=0;k<dim*dim;k++)
    {
        *(etiquetas+k)=0;
        *(size+k)=0;
    }

    for (i=0; i<dim; i++)
    {

        for (j=0; j<dim; j++)
        {
            if (*(red+i*dim+j)>0){
            (*(etiquetas+*(red+i*dim+j)))++;//[00532] para etiqueta 0 y 1 el tamaño es cero
            }
        }
    }

    for(k=0;k<dim*dim;k++){
        if (*(etiquetas+k)>0)
        (*(size+*(etiquetas+k)))++; //va a estar ordenado de menor a mayor tamaño
    }//cantidad de fragmentos para todos los tamaños

		free(etiquetas);
		return 0;
}
