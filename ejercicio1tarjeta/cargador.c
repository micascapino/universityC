#include <stdio.h>

typedef struct{
char nroTarjeta[17];
float importe;
int cuotas;
}compra;

int maintxt(){

    compra c;
    FILE *arch, *txt;

    arch = fopen("gastos","wb");
    txt = fopen("gastostxt.txt","r");

    while(fscanf(txt, "%s %f %d", c.nroTarjeta, &c.importe, &c.cuotas) == 3){
        fwrite(&c,sizeof(compra),1,arch);
    }

    fclose(arch);
    fclose(txt);

    return 0;

}
