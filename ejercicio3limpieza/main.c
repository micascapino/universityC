#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char tipo[4];
char clase[10];
char articulo[15];
char descripcion[25];
int unidades;
float precioUnitario;
}stock;

int main()
{
    FILE *arch=fopen("stock","rb");
    stock s;
    char tipoActual[4], claseActual[10];
    int articulosClase,unidadesClase, articulosTipo,unidadesTipo;
    float stockClase,stockTipo;;

    if (arch == NULL){
        printf("EL ARCHIVO NO EXISTE");
    }
    else{
        fread(&s,sizeof(stock),1,arch);
        while (!feof(arch)){
            //fscanf(arch,"%s %s %s %s %d %f", s.tipo,s.clase,s.articulo,s.descripcion,&s.unidades,&s.precioUnitario);
            strcpy(tipoActual,s.tipo);
            articulosTipo=0; unidadesTipo=0; stockTipo=0;
            printf("********************************* TIPO: %s *********************************\n",tipoActual);
            while (!feof(arch) && !strcmp(tipoActual,s.tipo)){
                strcpy(claseActual,s.clase);
                printf("CLASE: %s\n",claseActual);
                articulosClase=0; unidadesClase=0; stockClase=0;
                printf("ARTICULO \t UNIDADES \t PRECIO UNITARIO \t STOCK VALORIZADO\n");
                while (!feof(arch) && !strcmp(tipoActual,s.tipo) && !strcmp(claseActual,s.clase)){
                    articulosClase++;
                    unidadesClase+=s.unidades;
                    stockClase+=s.unidades*s.precioUnitario;
                    printf("%s \t %d \t \t $%.2f \t \t $%.2f\n", s.articulo, s.unidades, s.precioUnitario, (s.unidades*s.precioUnitario));
                    //fscanf(arch,"%s %s %s %s %d %f", s.tipo,s.clase,s.articulo,s.descripcion,&s.unidades,&s.precioUnitario);
                    fread(&s,sizeof(stock),1,arch);
                }
                articulosTipo+=articulosClase;
                stockTipo+=stockClase;
                unidadesTipo+=unidadesClase;
                printf("\nDATOS DE LA CLASE: \nUnidades: %d \t Stock Valorizado: $%.2f \t Cantidad de Articulos: %d\n\n",unidadesClase,stockClase,articulosClase);
            }
        printf("DATOS DEL TIPO: Unidades: %d \t Stock Valorizado: $%.2f \t Cantidad de Articulos: %d\n\n",unidadesTipo,stockTipo,articulosTipo);

        }


        fclose((arch));
    }
    return 0;
}
