#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char sucursal[3];
char seccion[4];
char nEmpleado[25];
float sueldo;
}pagos;

int main()
{
    FILE *arch=fopen("regPago","rb");
    pagos p;
    char sucActual[3], secActual[4];
    float totSucursal,totSeccion;
    if (arch != NULL){
        fread(&p,sizeof(pagos),1,arch);
        while (!feof(arch)){
            //fscanf(arch,"%s %s %s %f", p.sucursal,p.seccion, p.nEmpleado, &p.sueldo);
            strcpy(sucActual,p.sucursal);
            totSucursal=0;
            printf("SUCURSAL: %s\n",sucActual);
            printf("SECCION: \n");
            while (!feof(arch) && !strcmp(sucActual,p.sucursal)){
                totSeccion=0;
                strcpy(secActual,p.seccion);

                while (!feof(arch) && !strcmp(sucActual,p.sucursal) && !strcmp(secActual,p.seccion)){
                    totSeccion+=p.sueldo;
                    //fscanf(arch,"%s %s %s %f", p.sucursal,p.seccion, p.nEmpleado, &p.sueldo);
                    fread(&p,sizeof(pagos),1,arch);
                }
                totSucursal+=totSeccion;
                printf("\t%s $%.2f\n", secActual,totSeccion);
            }
             printf("TOTAL A SER ABONADO EN SUCURSAL %s: $%.2f\n\n",sucActual,totSucursal);
        }

    fclose(arch);
    }
    else{
        printf("El archivo se murio!\n");
    }
    return 0;
}
