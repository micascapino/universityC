#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
int seccion;
char legajo[6];
float importe;
}pagos;

int main()
{
    FILE *arch=fopen("pagos","rb");
    pagos p;
    int secActual,cantBonif,cantEmp;
    float acumBonif,bonTotal;
    char legajoActual[6];

    if (arch == NULL){
        printf("El archivo no existe");
    }
    else{
        fread(&p,sizeof(pagos),1,arch);
        while(!feof(arch)){
            //fscanf(arch,"%d %s %f", &p.seccion, p.legajo, &p.importe);
            secActual = p.seccion;
            printf("SECCION %d \n",secActual);
            printf("LEGAJO DEL EMPLEADO \t BONIFICACION PROMEDIO\n");
            bonTotal=0; cantEmp=0;
            while (!feof(arch) && (secActual == p.seccion)){
                strcpy(legajoActual,p.legajo);
                cantBonif=0; acumBonif=0;
                while (!feof(arch) && (secActual == p.seccion) && !strcmp(legajoActual, p.legajo)){
                    cantBonif++;
                    acumBonif+=p.importe;
                    //fscanf(arch,"%d %s %f", &p.seccion, p.legajo, &p.importe);
                    fread(&p,sizeof(pagos),1,arch);
                }
                bonTotal+=acumBonif/cantBonif;
                cantEmp++;
                printf("%s \t\t\t $%.2f\n",legajoActual,acumBonif/cantBonif);
            }
            printf("El promedio de bonificaciones de esta seccion es: $%.2f\n \n",bonTotal/cantEmp);
        }
    }
    return 0;
}
