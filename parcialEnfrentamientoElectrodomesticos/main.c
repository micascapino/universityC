#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char articulo[5];
int cantArts;
int codRubro;
float peso;
}informe;

typedef struct{
char articulo[5];
int cantArts;
}remito;

typedef struct{
int codRubro;
char descripcion[20];
char fragil;
}rubro;

void cargaInformeRecepcion();
void cargaRemitoProveedor();
void cargaRubros();
void procesa();
void cargaTabla(rubro tabla[], int *n);
void muestraTabla(rubro tabla[],int n);
int buscaPos(rubro tabla[], int rub);

int main()
{
    //cargaInformeRecepcion();
    //cargaRemitoProveedor();
    //cargaRubros();
    procesa();
    return 0;
}

void cargaInformeRecepcion(){
    informe r;
    FILE *arch, *txt;

    arch = fopen("informe","wb");
    txt = fopen("informetxt.txt","r");

    while(fscanf(txt,"%s %d %d %f",r.articulo,&r.cantArts,&r.codRubro, &r.peso) == 4){
        fwrite(&r,sizeof(informe),1,arch);
    }
    fclose(arch);
    fclose(txt);
}

void cargaRemitoProveedor(){
    remito r;
    FILE *arch, *txt;

    arch = fopen("remito","wb");
    txt = fopen("remitotxt.txt","r");

    while(fscanf(txt,"%s %d",r.articulo,&r.cantArts) == 2){
        fwrite(&r,sizeof(remito),1,arch);
    }
    fclose(arch);
    fclose(txt);
}

void cargaRubros(){
    rubro r;
    FILE *arch, *txt;

    arch = fopen("rubro","wb");
    txt = fopen("rubrotxt.txt","r");

    while(fscanf(txt,"%d %s %c",&r.codRubro, r.descripcion, &r.fragil) == 3){
        fwrite(&r,sizeof(rubro),1,arch);
    }
    fclose(arch);
    fclose(txt);

}

void procesa(){
    FILE *archRecep, *archRemito;
    informe m;
    remito r;
    rubro tabla[10];
    int coincidentes=0,n,pos,i,fragiles=0,total=0;
    int vec[10]={0};

    cargaTabla(tabla,&n);
    archRecep=fopen("informe","rb");
    archRemito=fopen("remito","rb");
    if (archRecep == NULL || archRemito == NULL)
        printf("No se encuentra archivo");
    else{
        fread(&m,sizeof(informe),1,archRecep);
        fread(&r,sizeof(remito),1,archRemito);
        printf("# Diferencias\n");
        while (!feof(archRecep) && !feof(archRemito)){
            if (!strcmp(m.articulo,r.articulo)){
                if (m.cantArts == r.cantArts)
                    coincidentes++;
                else
                    printf("Articulo %s con diferencia en catidad %d en Informe Recep, %d en Remito Proveedor\n",m.articulo,m.cantArts,r.cantArts);
                pos=buscaPos(tabla,m.codRubro);
                vec[pos]+=m.cantArts;
                fread(&m,sizeof(informe),1,archRecep);
                fread(&r,sizeof(remito),1,archRemito);
            }
            else if (strcmp(m.articulo,r.articulo)<0){
                printf("Articulo %s por %d solo existe en Informe Recep\n",m.articulo,m.cantArts);
                pos=buscaPos(tabla,m.codRubro);
                vec[pos]+=m.cantArts;
                fread(&m,sizeof(informe),1,archRecep);
            }
            else{
                printf("Articulo %s por %d solo existe en Remito Proveedor.\n",r.articulo,r.cantArts);
                fread(&r,sizeof(remito),1,archRemito);
            }
        }

     printf("\n# Cantidad de articulos coincidentes: %d\n",coincidentes);
     printf("\n# Resumen por Rubro Articulos registrados en Informe de Recepcion:\n");
     printf("Rubro \tCantidad\n");
     for(i=0;i<n;i++){
        if (vec[i] != 0){
            printf("%d-%s\t%d\n",tabla[i].codRubro,tabla[i].descripcion,vec[i]);
            if (tabla[i].fragil == 'S')
                fragiles+=vec[i];
            total+=vec[i];
        }
     }
     printf("\n#Porcentaje de articulos fragiles: %.2f %%\n",(fragiles/(float)total)*100);
    }
}

void cargaTabla(rubro tabla[], int *n){
FILE *arch = fopen("rubro","rb");
(*n)=0;
fread(&tabla[*n],sizeof(rubro),1,arch);
while (!feof(arch)){
    (*n)++;
    fread(&tabla[*n],sizeof(rubro),1,arch);
}
fclose(arch);
}

void muestraTabla(rubro tabla[],int n){
int i;
for (i=0;i<n;i++)
    printf("%d %s %c\n",tabla[i].codRubro,tabla[i].descripcion,tabla[i].fragil);
}

int buscaPos(rubro tabla[], int rub){
int i=0;
while (tabla[i].codRubro != rub)
    i++;
return i;}
