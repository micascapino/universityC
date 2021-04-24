#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
int nroSucursal;
char codVendedor[6];
int nroFactura;
float importe;
}ventas;

int main()
{
    ventas v;
    int sucursalActual,cantVentas,maxVentas;
    char vendedorActual[6], maxVendedor[6],maxVendFacturado[6],maxVendFacturadoGlobal[6];
    float facturacion,maxFacturacion,maxFacturacionGlobal=-1;
    FILE *arch=fopen("ventas","rb");

    if (arch == NULL){
        printf("El archivo no existe!\n");
    }
    else{
        printf("SUCURSAL \t CODIGO DEL VENDEDOR \t CANT. DE VENTAS\n");
        fread(&v,sizeof(ventas),1,arch);
        while (!feof(arch)){
            //fscanf(arch,"%d %s %d %f",&v.nroSucursal,v.codVendedor,&v.nroFactura,&v.importe);
            sucursalActual=v.nroSucursal;
            maxVentas=-1; maxFacturacion=-1;
            while(!feof(arch)&& (sucursalActual==v.nroSucursal)){
                strcpy(vendedorActual,v.codVendedor);
                cantVentas=0; facturacion=0;
                while(!feof(arch)&& (sucursalActual==v.nroSucursal) && !strcmp(vendedorActual,v.codVendedor)){
                    cantVentas++;
                    facturacion+=v.importe;
                    //fscanf(arch,"%d %s %d %f",&v.nroSucursal,v.codVendedor,&v.nroFactura,&v.importe);
                    fread(&v,sizeof(ventas),1,arch);
                }
                //al terminar con cada vendedor comparo sus maximos numero para ver si supero alguno
                if (cantVentas > maxVentas){
                    maxVentas=cantVentas;
                    strcpy(maxVendedor,vendedorActual);
                }
                if (facturacion > maxFacturacion){
                    maxFacturacion=facturacion;
                    strcpy(maxVendFacturado,vendedorActual);
                }
            }
            printf("%d \t \t %s \t\t \t %d \n",sucursalActual,maxVendedor,maxVentas);
            if (maxFacturacion > maxFacturacionGlobal){
                strcpy(maxVendFacturadoGlobal,maxVendFacturado);
                maxFacturacionGlobal=maxFacturacion;
            }
        }
    printf("%s ES EL VENDEDOR CON MAYOR FACUTRACION %.2f",maxVendFacturadoGlobal,maxFacturacionGlobal);
    }
    return 0;
}
