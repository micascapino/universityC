#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char legajo[7];
char nom[25];
float totalVentas;
int facturaMayor;
float mayorVenta;
}ventas;

typedef struct{
char legajo[7];
int nroFactura;
float importe;
}diario;

void cargaArchivoMaestro();
void cargaArchivoDiario();
void muestraActualizado();
void actualiza();

int main(){
    cargaArchivoMaestro();
    cargaArchivoDiario();
    actualiza();
    muestraActualizado();

    return 0;
}

void cargaArchivoMaestro(){
    ventas v;
    FILE *arch,*txt;

    arch = fopen("ventas","wb");
    txt = fopen("ventastxt.txt","r");

    while(fscanf(txt,"%s %s %f %d %f",v.legajo,v.nom,&v.totalVentas,&v.facturaMayor,&v.mayorVenta) == 5)
        fwrite(&v,sizeof(ventas),1,arch);
    fclose(arch);
    fclose(txt);
}

void cargaArchivoDiario(){
    diario d;
    FILE *arch,*txt;

    arch = fopen("diario","wb");
    txt = fopen("diariotxt.txt","r");

    while(fscanf(txt,"%s %d %f",d.legajo,&d.nroFactura,&d.importe) == 3)
        fwrite(&d,sizeof(diario),1,arch);
    fclose(arch);
    fclose(txt);
}

void actualiza(){
    ventas m;
    diario d;
    float facturacion;
    char legajoActual[7];
    FILE *maestro,*archD,*actualizado;

    maestro=fopen("ventas","rb");
    actualizado=fopen("actualizado","wb");
    archD=fopen("diario","rb");

    if(maestro == NULL || archD == NULL)
        printf("Algun archivo no se encuentra");
    else{
        fread(&d,sizeof(diario),1,archD);
        fread(&m,sizeof(ventas),1,maestro);
        while (strcmp(m.legajo,"999999") || strcmp(d.legajo,"999999")){ //Solo se puede hacer si se tiene centinela en ambos.
            if (!strcmp(d.legajo,m.legajo)){
                strcpy(legajoActual,m.legajo);
                facturacion=0;
                while(strcmp(d.legajo,"999999") && !strcmp(legajoActual,d.legajo)){
                    facturacion+=d.importe;
                    if (d.importe > m.mayorVenta){
                        m.mayorVenta=d.importe;
                        m.facturaMayor=d.nroFactura;
                    }
                    fread(&d,sizeof(diario),1,archD);
                }
                m.totalVentas+=facturacion;
                printf("El empleado %s lleva generados $%.2f en comisiones.\n",legajoActual,(m.totalVentas*0.005));
                fwrite(&m,sizeof(ventas),1,actualizado);
                fread(&m,sizeof(ventas),1,maestro);
            }
            else if (strcmp(d.legajo,m.legajo) > 0){
                printf("El empleado %s lleva generados $%.2f en comisiones.\n",m.legajo,(m.totalVentas*0.005));
                fwrite(&m,sizeof(ventas),1,actualizado);
                fread(&m,sizeof(ventas),1,maestro);

            }
            else{
                    fread(&d,sizeof(diario),1,archD);
                /*esta en el diario pero no en el mensual, es una persona nueva?
                strcpy(legajoActual,d.legajo);
                strcpy(m.legajo,legajoActual);
                m.mayorVenta=0;
                while(!feof(archD) && !strcmp(legajoActual,d.legajo)){
                    facturacion+=d.importe;
                    if (d.importe > m.mayorVenta){
                        m.mayorVenta=d.importe;
                        m.facturaMayor=d.nroFactura;
                    }
                    fread(&d,sizeof(diario),1,archD);
                }
                m.totalVentas+=facturacion;
                printf("El empleado %s lleva generados $%.2f en comisiones.\n",legajoActual,(m.totalVentas*0.005));
                fwrite(&m,sizeof(ventas),1,actualizado);*/

            }


        }
        fclose(archD);
        fclose(maestro);
        fclose(actualizado);
        }

}

void muestraActualizado(){
    FILE *arch;
    ventas v;

    arch=fopen("actualizado","rb");
    if (arch == NULL)
        printf("No se genero el archivo o no se encuentra.");
    else{
        printf("\nLegajo \tNombre \t\tVentas \t\tFacturaMayor \tMayorVenta\n");
        fread(&v,sizeof(ventas),1,arch);
        while(!feof(arch)){
            printf("%s \t%s \t%.2f \t%d \t\t%.2f\n",v.legajo,v.nom,v.totalVentas,v.facturaMayor,v.mayorVenta);
            fread(&v,sizeof(ventas),1,arch);
        }
        fclose(arch);
    }
}
