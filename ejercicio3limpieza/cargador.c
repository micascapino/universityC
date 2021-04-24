#include <stdio.h>

typedef struct{
char tipo[4];
char clase[10];
char articulo[15];
char descripcion[25];
int unidades;
float precioUnitario;
}stock;

int maintxt(){

    stock s;
    FILE *arch, *txt;

    arch = fopen("stock","wb");
    txt = fopen("stocktxt.txt","r");

    while(fscanf(txt,"%s %s %s %s %d %f",s.tipo,s.clase,s.articulo,s.descripcion,&s.unidades,&s.precioUnitario) == 6){
        fwrite(&s,sizeof(stock),1,arch);
    }

    fclose(arch);
    fclose(txt);

    return 0;

}


