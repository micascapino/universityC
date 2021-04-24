#include <stdio.h>

typedef struct{
char sucursal[3];
char seccion[4];
char nEmpleado[25];
float sueldo;
}pagos;

int maintxt(){

    pagos p;
    FILE *arch, *txt;

    arch = fopen("regPago","wb");
    txt = fopen("pagostxt.txt","r");

    while(fscanf(txt, "%s %s %s %f",p.sucursal,p.seccion,p.nEmpleado,&p.sueldo) == 4){
        fwrite(&p,sizeof(pagos),1,arch);
    }

    fclose(arch);
    fclose(txt);

    return 0;

}

