char filename [255]
sprintf(filename, "data_L=%d.txt",L)
FILE+ fp=fopen(filename,"w")

for(p=p1; p<p2;p=p+dp)
{
  ...
  calcula ns
  ...
  fprintf(fp,"%f",p);
  for(k=o;k<L^2;k++){
    fprintf(fp," %f";(ns+k));
  }
  fprintf(fp,"\n");
}

//para leer

FILE* fp=fopen(fname,"r");
float p, ns[dim*dim]
int i= fscanf(fp, "%f", &p);
for(k=0; k<dim*dim; k++){
  int i=fscanf(fp," %f",ns+k)
}
