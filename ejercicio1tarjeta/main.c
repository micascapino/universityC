#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
char nroTarjeta[17];
float importe;
int cuotas;
}compra;


int main()
{
    FILE *arch;
    compra c;
    char tarjetaActual[17], financia;
    float total, mayorImporte;

    arch=fopen("gastos","rb");
    if (arch != NULL){
        printf("NRO. TARJETA \t \t TOTAL \t\t COMPRA MAYOR IMPORTE \t FINANCIACION\n");
        //fscanf(arch,"%s %f %d",c.nroTarjeta,&c.importe,&c.cuotas);
        fread(&c,sizeof(compra),1,arch);
        while (!feof(arch)){
            total = 0; mayorImporte=0; financia='N';
            strcpy(tarjetaActual,c.nroTarjeta);
            while (!feof(arch) && !strcmp(tarjetaActual,c.nroTarjeta)){
                total+=c.importe;
                if (mayorImporte < c.importe)
                    mayorImporte=c.importe;
                if (c.cuotas > 1 && financia !='S')
                    financia = 'S';
                fread(&c,sizeof(compra),1,arch);
                //fscanf(arch,"%s %f %d",c.nroTarjeta,&c.importe,&c.cuotas);
            }
            printf("%s \t $%.2f \t $%.2f %18c \n",tarjetaActual, total, mayorImporte, financia);
        }
    }
    return 0;
}
