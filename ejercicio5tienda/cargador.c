#include <stdio.h>

typedef struct{
int nroSucursal;
char codVendedor[6];
int nroFactura;
float importe;
}ventas;

int maintxt(){

    ventas v;
    FILE *arch, *txt;

    arch = fopen("ventas","wb");
    txt = fopen("ventastxt.txt","r");

    while(fscanf(txt,"%d %s %d %f",&v.nroSucursal,v.codVendedor,&v.nroFactura,&v.importe) == 4){
        fwrite(&v,sizeof(ventas),1,arch);
    }
    fclose(arch);
    fclose(txt);
    return 0;

}

